#include <iostream>
#include <map>
#include <string>
#include <vector>

class Context {
public:
    Context() {};

    Context(const Context &original, const std::string &key, const std::string &value) : map_{original.map_} {
        map_[key] = value;
    }
    Context* insertNewKeyValue(const std::string &key, const std::string &value) {
        auto new_context = new Context(*this, key, value);
        return new_context;
    }

    const std::string printContext() const {
        std::string output;
        for (const auto&[key, value]: map_)
            output += key + "=" + value;
        return output;
    }


private:
    std::map<std::string, std::string> map_;
};

namespace cr {
    void log(Context *ctx, const std::string message) {
        std::cout << ctx->printContext() << " " << message << "\n";
    }
}

class Frame {
public:
    Frame(const std::string &id) : id_{id} {}

    const std::string &id() const { return id_; }

private:
    const std::string id_;
};

void processFrame(Context *ctx, Frame *frame) {
    // add a call here to add a frame_id to the context
    ctx = ctx->insertNewKeyValue("frame_id", frame->id());
    cr::log(ctx, "started processFrame");
    // pretend we do something really complicated here
    cr::log(ctx, "finished processFrame");
}

void processAllFrames(Context *ctx, std::vector<Frame *> frames) {
    // add a call here to add a frame_count value to the context, which should
    // be the length of the frame vector
    ctx = ctx->insertNewKeyValue("frame_count", std::to_string(frames.size()));
    for (const auto f: frames) {
        cr::log(ctx, "about to call processFrame");
        processFrame(ctx, f);
        cr::log(ctx, "finished the call to processFrame");
    }
}

std::vector<Frame *> getFrames() {
    std::vector<Frame *> frames;
    for (int i = 0; i < 2; ++i) {
        auto frame = new Frame(std::to_string(1 + i));
        frames.push_back(frame);
    }
    return frames;
}

int main(int argc, char **argv) {
    auto frames = getFrames();
    auto ctx = new Context(); // create a context, somehow
    processAllFrames(ctx, frames);
    return 0;
}
