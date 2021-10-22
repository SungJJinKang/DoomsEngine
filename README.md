# Dooms Engine ( Game Engine )

## Game Engine

This project start from project making doom2 from scratch.     
But At some point, I was making Game Engine!!      
So I decided to change Project Goal.          

This game engine will be used in making my tiny home-made game.         

## Why Do This Project

i had made some indie games with Unity game engine [Google PlayStore](https://play.google.com/store/apps/details?id=com.milli.findkiller2&hl=ko)  [Google PlayStore1](https://play.google.com/store/apps/details?id=com.NintyNineMillion.FindKiller&hl=ko).   
But Unity gives everything what I need. I didn't have to know how does Unity Engine work behind Editor UI.   
So Even if i had made many games for 3 years, i couldn't make just tiny game without Game Engine still.   

It's suck    

So I decided making game without game engine.       
I don't know How long it will takes to complete this project.    
But I will complete this project!!    

if you wanna good and clean code for learning something, Find other project.      


## Video

[Game Engine Video](https://youtube.com/playlist?list=PLUg9a0kyCgTR3OhYZYSMauDmjv6D96pVz)              

## Key features

  * C++17                   

## Implemented features

  * Deferred Rendering ( https://youtu.be/TU9P8gcKsi8 )
  * Profiler (reference : https://youtu.be/tD4xRNB0M_Q) 
  * Logger
  * Memory Pool(limited use)
  * Homemade Math Library (https://github.com/SungJJinKang/LightMath_Cpp)     
  * Homemade Asset Importer ( I tried to make everything from scratch. but Finally I decided just integrating many 3rd asset importers to one system)
  * Multi Thread ViewFrustum Culling ( https://sungjjinkang.github.io/doom/c++/computergraphics/game/2021/04/02/viewfrustumculling.html )
  * Distance Culling ( https://docs.unrealengine.com/en-US/RenderingAndGraphics/VisibilityCulling/CullDistanceVolume/index.html ) ( not used )
  * Support SIMD ( Currently AVX1 )
  * HW Query Occlusion Culling, Conditional Rendering ( https://github.com/SungJJinKang/EveryCulling )
  * Asset Import Pipeline ( Automatically import assets located in asset folder )
  * JobSystem ( Thread Pool - https://github.com/SungJJinKang/JobSystem_cpp )
  * Collision, Raycasting, Picking ( implemented with BVH Tree ) ( https://youtu.be/ZASdCIKeG6s )
  * Overdraw Visualization ( implemented with Additive Blending ) ( https://youtu.be/fU3iBthe4Ws )
  * FrameBuffer, Texture Exporter ( https://youtu.be/T2XlHlOr95g )
  * Reflection System ( https://sungjjinkang.github.io/computerscience/2021/10/20/Reflection.html )
  * Fast Runtime Type Casting ( O(1), Not use dynamic_cast ( RTTI option is disabled ), https://github.com/SungJJinKang/Fast_Runtime_TypeCasting_cpp )        

## In Developing

  * Masked SW Occlusion Culling ( https://software.intel.com/content/dam/develop/external/us/en/documents/masked-software-occlusion-culling.pdf )      
  * Batching System ( Static Batch, Dynamic Batch )
  
## Dependency
I will try to make everything what i need.     
but i can't make some librarys like graphics api, audio api, some importers ....           

  * opengl 4.6       
  * glfw 3.3.2         
  * assimp       
  * DirectxTex        
  * concurrentqueue       
  * crossguid         
  * free type2       

## WARNING
On AMD on Board GPU, OpenGL sometimes makes driver error.      
Use NVIDEA GPU.     

## Coding Standard
[English](https://docs.google.com/document/d/1cT8EPgMXe0eopeHvwuFmbHG4TJr5kUmcovkr5irQZmo/edit)   
[Korean](https://docs.popekim.com/ko/coding-standards/cpp)

## Development Blog
[Korean Blog](https://sungjjinkang.github.io/) 

## Thanks
![WoCR0sCfffff](https://user-images.githubusercontent.com/33873804/103935734-5e92e300-516a-11eb-9afd-ab48b5f65791.png)
