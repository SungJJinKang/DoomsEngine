
## Plan

- Job pool system. [Thread Pool](https://github.com/SungJJinKang/ThreadPool_Cpp)       
- Lock free Queue [ConcurrentQueue](https://github.com/cameron314/concurrentqueue)       
- Priority Queue ( Jobs needed to excuted first, Threads will process this first )      
- Restrain putting Job what can make Race Condition ( This will make best result )           
- Don't use more threads than CPU core count. ( reduce Context switching cost )      

## Best Result
               Thread1              Thread2               Thread3               Thread4~        
Time 1       PhysicsJob            PhysicsJob            PhysicsJob            PhysicsJob     
Time 2       PhysicsJob            PhysicsJob            PhysicsJob            PhysicsJob       
Time 3   Finish PhysicsJob      Finish PhysicsJob     Finish PhysicsJob     Finish PhysicsJob     
Time 4      Renderingjob          Renderingjob          Renderingjob          Renderingjob      
Time 5      Renderingjob          Renderingjob          Renderingjob          Renderingjob     
Time 6      Renderingjob          Renderingjob          Renderingjob          Renderingjob     
Time 7  Finish Renderingjob     Finish Renderingjob   Finish Renderingjob   Finish Renderingjob        

## Bad Result
               Thread1              Thread2               Thread3               Thread4~        
Time 1       PhysicsJob            PhysicsJob            PhysicsJob            PhysicsJob     
Time 2       PhysicsJob            PhysicsJob            PhysicsJob            PhysicsJob       
Time 3    Finish PhysicsJob     Finish PhysicsJob     Finish PhysicsJob        PhysicsJob    
Time 4        Sleeping              Sleeping              Sleeping             PhysicsJob       
Time 5        Sleeping              Sleeping              Sleeping             PhysicsJob       
Time 6        Sleeping              Sleeping              Sleeping             PhysicsJob   
Time 7        Sleeping              Sleeping              Sleeping          Finish PhysicsJob     

## Bad Result Solution Strategy

- Push Job uniformly : but It's hard to anticipate how long the job takes.    
- Push simple Job : This will make threads finish jobs at the same time.      
- Job Stealing : If a thread finished assigned jobs, the thread steal other thread's job.          
- 

## Reference
  * https://www.youtube.com/watch?v=M1e9nmmD3II