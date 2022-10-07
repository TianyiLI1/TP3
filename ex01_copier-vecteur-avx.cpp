/**
  * Copie d'un tableau dans un autre avec les intrinseques AVX.
  * A compiler avec les drapeaux -O2 -mavx2.
  */

//compiler: clang

#include <immintrin.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>

#define NREPET 102400

void afficherUsage()
{ 
  printf("Usage: ./copier-vecteur-avx [taille-du-tableau]\n");
}

int main(/*int argc, char **argv*/)
{
 /* if (argc < 2) {
    afficherUsage();
    return 1;
  }*/
 /* int dim = std::atoi(argv[1]);*/
int dim=8;
  // Allouer et initialiser deux tableaux de flottants de taille dim alignes par 32 octets

float a0[8]={0,0,0,0,0,0,0,0};
    float a1[8]={0,1,2,3,4,5,6,7};
    float *tab0=(float *) _mm_malloc(dim*sizeof (float ),32) ;
  float *tab1=(float *) _mm_malloc(dim*sizeof (float ),32);

  // A FAIRE ...

    for (unsigned i = 0; i < dim; ++i) {

     tab1[i]=a1[i];
     tab0[i]=a0[i];
    }



  // Copier tab0 dans tab1 de manière scalaire~(code non-vectorise).
  // On repete NREPET fois pour mieux mesurer le temps d'execution
  auto start = std::chrono::high_resolution_clock::now();
  for (int repet = 0; repet < NREPET; repet++) {

      for (unsigned i = 0; i < dim; ++i) {
          tab0[i]=tab1[i];
      }
  }



  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diffSeq = end-start;
  std::cout << std::scientific << "Copier sans AVX: " << diffSeq.count() / NREPET << "s" << std::endl;

    for (unsigned i = 0; i < dim; ++i) {

        tab0[i]=a0[i];
        tab1[i]=a1[i];

    }

  // Copier tab0 dans tab1 de maniere vectorisee avec AVX
  start = std::chrono::high_resolution_clock::now();

    __m256 r1;
  for (int repet = 0; repet < NREPET; repet++) {


          r1= _mm256_load_ps(tab1);
          _mm256_store_ps(tab0,r1);

  }
float x[dim];
    for (int i = 0; i < dim; ++i) {
        x[i]=tab0[i];
    }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diffPar = end-start;
  std::cout << std::scientific << "Copier avec AVX: " << diffPar.count() / NREPET << "s" << std::endl;
  // Afficher l'acceleration et l'efficacite
  std::cout<<"Acceleration avec AVX en copie: "<<diffSeq/diffPar<<std::endl;

  // Copier tab0 dans tab1 de maniere vectorisee avec AVX et deroulement de facteur 4
  float t0[dim/4];float t1[dim/4];float t2[dim/4];float t3[dim/4];
    float i0[dim/4];float i1[dim/4];float i2[dim/4];float i3[dim/4];
    for (int i = 0; i < dim/4; ++i) {
        t0[i]=tab1[i];
        t1[i]=tab1[dim/4+i];
        t2[i]=tab1[2*dim/4+i];
        t3[i]=tab1[3*dim/4+i];
    }
    __m256 c0;
    __m256 c1;
    __m256 c2;
    __m256 c3;

  start = std::chrono::high_resolution_clock::now();
  for (int repet = 0; repet < NREPET; repet++) {

      c0= _mm256_load_ps(t0);
      _mm256_store_ps(i0,c0);

      c1= _mm256_load_ps(t1);
      _mm256_store_ps(i1,c1);

      c2= _mm256_load_ps(t2);
      _mm256_store_ps(i2,c2);

      c3= _mm256_load_ps(t3);
      _mm256_store_ps(i3,c3);

      for (int i = 0; i < dim/4; ++i) {
          tab0[i]=i0[i];
          tab0[i+dim/4]=i1[i];
          tab0[i+2*dim/4]=i2[i];
          tab0[i+3*dim/4]=i3[i];
      }

  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diffParDeroule = end-start;
  std::cout << std::scientific << "Copier avec AVX et deroulement: " << diffParDeroule.count() / NREPET << "s" << std::endl;
  // Afficher l'acceleration et l'efficacite
  // A FAIRE ...

  // Desallouer les tableaux tab0 et tab1
  // A FAIRE ...

  return 0;
}
