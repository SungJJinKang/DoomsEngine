# Dooms Engine ( Game Engine ) ( 2021.01.07 ~ )
  
## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Features

  * C++17
  * C# ( used for making engine tools )    
  * Target Compiler : MSVC ( clang is used for generating reflection data )
  * OpenGL
  * Component based System
  * Deferred Rendering ( https://youtu.be/TU9P8gcKsi8 )
  * Homemade Math Library (https://github.com/SungJJinKang/LightMath_Cpp)     
  * Multi Thread ViewFrustum Culling ( https://sungjjinkang.github.io/doom/c++/computergraphics/game/2021/04/02/viewfrustumculling.html )
  * Support SIMD ( Currently AVX2 )
  * HW Query Occlusion Culling, Conditional Rendering ( https://github.com/SungJJinKang/EveryCulling )
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * JobSystem ( Thread Pool - https://github.com/SungJJinKang/JobSystem_cpp )
  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( https://youtu.be/ZASdCIKeG6s )
  * Object Management System for preventing memory leak ( https://sungjjinkang.github.io/computerscience/gameengine/2021/09/25/dangling_pointer.html )
  * Fast Runtime Type Casting ( writing manually type name is not required, reflection data is used. check reflection.h files ) ( time complexicity is always O(1), dynamic_cast isn't used ( RTTI option is disabled ), https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp )        
  * Automatic Reflection Data Generation System. ( video - https://youtu.be/KGihaYTzqG8 ) ( clrefelct_automation - https://github.com/SungJJinKang/clReflect_automation )
  * Customizing Reflection Open Source Library ( video - https://youtu.be/9DKGvkdR6zw ) ( Customized clReflect - https://github.com/SungJJinKang/clReflect_ForDoomsEngine )
  * Integrate imgui with reflection system. ( DObjects, std::vector, std::array, std::unique_ptr... is supported, video - https://youtu.be/wxZIGoTRcpo )
  * Garbage Collector using reflection system ( Mark ( multithread ) - Sweep algorithm, std::array, std::vector is also supported, nullify pointer referencing destroyed object, 한국어 블로그 - https://sungjjinkang.github.io/computerscience/2021/12/01/reflection_gc.html, video - https://youtu.be/E4CNOIXYQnQ )
  * Masked SW ( CPU ) Occlusion Culling ( 95%, video : [https://youtu.be/tMgokVljvAY](https://youtu.be/tMgokVljvAY), [https://youtu.be/1IKTXsSLJ5g](https://youtu.be/1IKTXsSLJ5g), source code direcotry - https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/MaskedSWOcclusionCulling, 개발 일지 : https://sungjjinkang.github.io/computerscience/computergraphics/2021/12/31/masked_sw_occlusion_culling.html, reference : https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf, https://www.slideshare.net/IntelSoftware/masked-software-occlusion-culling ) 
  
## Currently working on

  * change graphics api!!! ( 0%, OpenGL to DirectX11 )
  * implement physical based rendering ( https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf )
 
## To Develop
 
  * Hierarchical Shadow Map

## Screenshot
![20211213050637](https://user-images.githubusercontent.com/33873804/145727751-74daefb4-a6b1-4b3c-94d3-56a52c5c0861.png)

## Coding Standard

[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)


## Development Blog

[Korean Blog](https://sungjjinkang.github.io/) 
