# Dooms Engine ( Game Engine ) ( 2021.01.07 ~ )
  
## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Features

  * C++17
  * C# ( used in making engine tools )    
  * Target Compiler : MSVC ( clang is used for generating reflection data )
  * Window Platform is supported
  * OpenGL
  * Deferred Rendering ( https://youtu.be/TU9P8gcKsi8 )
  * Profiler (reference : https://youtu.be/tD4xRNB0M_Q) 
  * Logger
  * Memory Pool(limited use)
  * Homemade Math Library (https://github.com/SungJJinKang/LightMath_Cpp)     
  * Homemade Asset Importer ( I tried to make everything from scratch. but Finally I decided just integrating many 3rd asset importers to one system)
  * Multi Thread ViewFrustum Culling ( https://sungjjinkang.github.io/doom/c++/computergraphics/game/2021/04/02/viewfrustumculling.html )
  * Distance Culling ( https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html ) ( default : disabled )
  * Support SIMD ( Currently AVX2 )
  * HW Query Occlusion Culling, Conditional Rendering ( https://github.com/SungJJinKang/EveryCulling )
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * JobSystem ( Thread Pool - https://github.com/SungJJinKang/JobSystem_cpp )
  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( https://youtu.be/ZASdCIKeG6s )
  * Overdraw Visualization ( implemented with Additive Blending ) ( https://youtu.be/fU3iBthe4Ws )
  * Object Management System for preventing memory leak ( https://sungjjinkang.github.io/computerscience/gameengine/2021/09/25/dangling_pointer.html )
  * FrameBuffer, Texture Exporter ( https://youtu.be/T2XlHlOr95g )
  * Fast Runtime Type Casting ( O(1), Not use dynamic_cast ( RTTI option is disabled ), https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp )        
  * Automatic Reflection Data Generation System. ( video - https://youtu.be/KGihaYTzqG8 ) ( clrefelct_automation - https://github.com/SungJJinKang/clReflect_automation )
  * Customizing Reflection Open Source Library ( video - https://youtu.be/9DKGvkdR6zw ) ( Customized clReflect - https://github.com/SungJJinKang/clReflect )
  * Integrate imgui with reflection system. ( video - https://youtu.be/wxZIGoTRcpo )

## Currently working on

  * change graphics api ( 0%, OpenGL to DirectX12 )
  * Masked SW Occlusion Culling ( 20%, work directory - https://github.com/SungJJinKang/EveryCulling/tree/main/CullingModule/MaskedSWOcclusionCulling ) ( reference : https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf )       
  * fully implement engine ui ( 30%, use imgui! - https://github.com/ocornut/imgui )     
 
## To Develop

  * Batching System ( Static Batch, Dynamic Batch )        
  * Refactoring ( Remove a lot of dependency between modules, classes )
  * Unreal Engine Style Garbage Collector ( reference : https://www.slideshare.net/QooJuice/ue4-garbage-collection-2 )
  * Hot Reload ( similar to Unreal Engine's )
  * implement clReflect x64 Function Call Assembly ( https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170 )


## Coding Standard

[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)


## Development Blog

[Korean Blog](https://sungjjinkang.github.io/) 
