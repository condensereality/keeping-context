# keeping-context

## Task
### The problem

As a lot of people do, we have logging in our codebase. The problem with logging is that, in general, there’s very little contextual information - just a mess of output that’s hard to sort through. For example, we process hundreds of frames per second in our rig - if something goes wrong with just one, how do we quickly isolate the logs relating to just that frame?

Frame is just an example of course - since we aggregate all our logs into one place, we will want to annotate each log line with (for example) a rig ID, a service, or even the name of subsystem emitting the log line.

So, this means we have the following requirements:

- Log lines should be annotated with key/value pairs
- Those annotations are *contextual* - annotations are added based on context

### Writing the code

As you can see, we’ll need the following capabilities:

- Create an empty context
- Add a value to a context, or somehow get a context based on the old one with a new value in it
- Get the key/value pairs of everything that’s in the context so the `cr::log` function can build its output

For the sake of simplicity, assume all keys and values added to the context are strings.

### Expected output

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

## Compiling the example code
A minimal example required for the keeping context interview question

Compile using

```
g++ -std=c++17 keeping_context.cpp -o KeepingContext
```
and then run the code using
```
./KeepingContext
```
