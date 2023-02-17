# std::find simd version

std::find doesn't use simd intrinsics. ( check [https://gms.tf/stdfind-and-memchr-optimizations.html](https://gms.tf/stdfind-and-memchr-optimizations.html) )             

So i thought simd can make std::find faster for some types.       

## Feature

- avx2 intrinsic is used
- You don't need worry about alignment problem. ( this library handle it )          

## Requirement

- iterator's value type should be scalar type and type size of it should be 1 or 2 or 4 or 8
- iterator should be random access iterator
- require avx2 option
- require c++ 11

## Usage
```
std::vector<short> a;
a.reserve(1001);
for (unsigned short i = 0; i <= 1000; i++)
{
  a.push_back(i);
}

for (short i = 0; i < 1000; i++)
{
  fast_find_simd::find_simd(a.begin(), a.end(), (short)i);
}
```

## Performance Comparison
tested on release mode, msvc, x64, windows               
![20211128031529](https://user-images.githubusercontent.com/33873804/143701373-1c8aafbe-6131-4538-9d60-5432b84cd87c.png)


## To develop

- add find_last_of_simd
- implement partial template specialization of std::find ( Is this possible? )        
- support for avx512 intrinsic ( ex) _mm256_cmpeq_epi8_mask ) ( not tested. https://github.com/SungJJinKang/std_find_simd/tree/avx512_version )         
- more optimization ( [https://www.reddit.com/r/simd/comments/r3upl8/comment/hmd5uw9/?utm_source=share&utm_medium=web2x&context=3](https://www.reddit.com/r/simd/comments/r3upl8/comment/hmd5uw9/?utm_source=share&utm_medium=web2x&context=3) )           

