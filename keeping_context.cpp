#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Context {
public:
    using Self = Context;
    using Ptr = std::shared_ptr<Self>;

    Context() {};

    static Ptr New() { return std::make_shared<Self>(); }

    Context(const Context &original, const std::string &key, const std::string &value) : map_{original.map_} {
        map_[key] = value;
    }

    Ptr insertNewKeyValue(const std::string &key, const std::string &value) {
        return std::make_shared<Self>(*this, key, value);
    }

    const std::string printContext() const {
        std::string output;
        for (const auto&[key, value]: map_)
            output += key + "=" + value + " ";
        return output;
    }


private:
    std::map<std::string, std::string> map_;
};

namespace cr {
    void log(const Context::Ptr ctx, const std::string message) {
        std::cout << ctx->printContext() << message << "\n";
    }
}

class Frame {
public:
    using Self = Frame;
    using Ptr = std::shared_ptr<Self>;

    Frame(const std::string &id) : id_{id} {}
    static Ptr New(const std::string &id) { return std::make_shared<Self>(id); }

    const std::string &id() const { return id_; }

private:
    const std::string id_;
};

void processFrame(Context::Ptr ctx, const Frame::Ptr frame) {
    // add a call here to add a frame_id to the context
    ctx = ctx->insertNewKeyValue("frame_id", frame->id());
    cr::log(ctx, "started processFrame");
    // pretend we do something really complicated here
    cr::log(ctx, "finished processFrame");
}

void processAllFrames(Context::Ptr ctx, const std::vector<Frame::Ptr> frames) {
    // add a call here to add a frame_count value to the context, which should
    // be the length of the frame vector
    ctx = ctx->insertNewKeyValue("frame_count", std::to_string(frames.size()));
    for (const auto f: frames) {
        cr::log(ctx, "about to call processFrame");
        processFrame(ctx, f);
        cr::log(ctx, "finished the call to processFrame");
    }
}

const std::vector<Frame::Ptr> getFrames() {
    std::vector<Frame::Ptr> frames;
    for (int i = 0; i < 2; ++i){
        const auto frame = Frame::New(std::to_string(1 + i));
        frames.push_back(frame);
    }
    return frames;
}

int main(int argc, char **argv) {
    const auto frames = getFrames();
    auto ctx = Context::New(); // create a context, somehow
    processAllFrames(ctx, frames);
    return 0;
}
