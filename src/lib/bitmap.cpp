#include "bitmap.h"
#include <ImfInputFile.h>
#include <ImfOutputFile.h>
#include <ImfChannelList.h>
#include <ImfStringAttribute.h>
#include <ImfVersion.h>

extern "C" {

void bitmap_save_exr(struct Bitmap *bitmap, char *c_filename) {
    printf("\nWriting a %zu x %zu image to %s\n", bitmap->W, bitmap->H, c_filename);
    std::string filename = c_filename;
    assert(filename.substr(filename.size() - 4, 4) == ".exr" && "EXR filename should end with `.exr`");

    Imf::Header header((int) bitmap->W, (int) bitmap->H);
    header.insert("comments", Imf::StringAttribute("Generated by team32"));

    Imf::ChannelList &channels = header.channels();
    channels.insert("R", Imf::Channel(Imf::FLOAT));
    channels.insert("G", Imf::Channel(Imf::FLOAT));
    channels.insert("B", Imf::Channel(Imf::FLOAT));

    Imf::FrameBuffer frameBuffer;
    size_t compStride = sizeof(float), pixelStride = 3 * compStride, rowStride = pixelStride * bitmap->W;

    char *ptr = reinterpret_cast<char *>(bitmap->pixels.data);
    frameBuffer.insert("R", Imf::Slice(Imf::FLOAT, ptr, pixelStride, rowStride)), ptr += compStride;
    frameBuffer.insert("G", Imf::Slice(Imf::FLOAT, ptr, pixelStride, rowStride)), ptr += compStride;
    frameBuffer.insert("B", Imf::Slice(Imf::FLOAT, ptr, pixelStride, rowStride));

    Imf::OutputFile file(c_filename, header);
    file.setFrameBuffer(frameBuffer);
    file.writePixels((int) bitmap->H);
}

}