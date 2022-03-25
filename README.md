# keeping-context
A minimal example required for the keeping context interview question

Compile using

```
g++ -std=c++17 keeping_context.cpp -o KeepingContext
```
and then run the code using
```
./KeepingContext
```

## Expected output

```
frame_count=2 about to call processFrame
frame_count=2 frame_id=1 started processFrame
frame_count=2 frame_id=1 finished processFrame
frame_count=2 finished the call to processFrame
frame_count=2 about to call processFrame
frame_count=2 frame_id=2 started processFrame
frame_count=2 frame_id=2 finished processFrame
frame_count=2 finished the call to processFrame
```