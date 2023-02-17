# EasyDirtyChecker

## HOW WORKS?

```
          Sender               Receiver1                Receiver2     
        (Only One)     
Frame 1     X                     X                         X

Frame 2     O ( Notify Dirty )    O ( Receive Dirty )       O ( Receive Dirty ) 

Frame 3     X                     O ( Not Reset )           O

Frame 4     X                     X ( Reset Dirty )         O

Frame 5     X                     X                         O
```

Pass DirtyReceiver pointer through DirtySender::AddDirtyReceiver
You can add multiple receiver to DirtySender ( Use DirtyReceiver::SetDirtySender )      
You don't need remove receiver from DirtySender's receiver List when Receiver class is destructed. ( RAII )     

Each Receivers will receive dirty value from Sender ( Only One ).       
And Reveivers will maintain dirty value until they reset their dirty themself       

WARNING : This is not thread-safe. You should implement it yourself.

## EXAMPLE

```c++
DirtySender mDirtySender{};

DirtyReceiver mDirtyReceiver{};
mDirtySender.AddDirtyReceiver(&mDirtyReceiver); // Register DirtyReceiver to DirtySender
         
mDirtySender.NotifyDirty(); // DirtySender notify dirty true to Receivers(Local Dirtys)
 
if(mDirtyReceiver.GetIsDirty(true)) // Local Dirty Check if dirty is true, if it's dirty true then Reset it's dirty variable false And return true
{//if dirty is true
          ~~
}
```
