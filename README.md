# Dooms Engine ( Game Engine )

## Key features

  * C++17
  * C# ( used in making engine tools )      
  * Target Compiler : MSVC ( clang is used for generating reflection data )
  * Window Platform
  
## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Implemented features

  * Deferred Rendering ( https://youtu.be/TU9P8gcKsi8 )
  * Profiler (reference : https://youtu.be/tD4xRNB0M_Q) 
  * Logger
  * Memory Pool(limited use)
  * Homemade Math Library (https://github.com/SungJJinKang/LightMath_Cpp)     
  * Homemade Asset Importer ( I tried to make everything from scratch. but Finally I decided just integrating many 3rd asset importers to one system)
  * Multi Thread ViewFrustum Culling ( https://sungjjinkang.github.io/doom/c++/computergraphics/game/2021/04/02/viewfrustumculling.html )
  * Distance Culling ( https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html ) ( not used )
  * Support SIMD ( Currently AVX2 )
  * HW Query Occlusion Culling, Conditional Rendering ( https://github.com/SungJJinKang/EveryCulling )
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * JobSystem ( Thread Pool - https://github.com/SungJJinKang/JobSystem_cpp )
  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( https://youtu.be/ZASdCIKeG6s )
  * Overdraw Visualization ( implemented with Additive Blending ) ( https://youtu.be/fU3iBthe4Ws )
  * FrameBuffer, Texture Exporter ( https://youtu.be/T2XlHlOr95g )
  * Reflection System ( use https://github.com/Celtoys/clReflect )
  * Fast Runtime Type Casting ( O(1), Not use dynamic_cast ( RTTI option is disabled ), https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp )        

## In Developing

  * Automation System Generating Reflection Data ( https://github.com/SungJJinKang/clReflect_automation )
  * Masked SW Occlusion Culling ( https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf )      
  * Batching System ( Static Batch, Dynamic Batch )

## Coding Standard
[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)

## Development Blog
[Korean Blog](https://sungjjinkang.github.io/) 
