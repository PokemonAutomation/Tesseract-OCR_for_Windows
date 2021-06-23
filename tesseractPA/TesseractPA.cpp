/*  Tesseract Wrapper
 * 
 *  From: https://github.com/PokemonAutomation/
 * 
 */

#include "allheaders.h"
#include "baseapi.h"
#include "TesseractPA.h"

#include <iostream>
using std::cout;
using std::endl;



class TesseractImage{
public:
    ~TesseractImage(){
        pixDestroy(&m_image);
    }
    TesseractImage(const char* path)
        : m_image(pixRead(path))
    {}

    operator Pix*(){
        return m_image;
    }

private:
    Pix* m_image;
};



struct TesseractAPI_internal{
    tesseract::TessBaseAPI m_api;

    TesseractAPI_internal(const char* path, const char* language){
        if (m_api.Init(path, language)){
            throw "Could not initialize TesseractAPI.";
        }
    }

};



TesseractAPI_internal* TesseractAPI_construct(const char* path, const char* language){
    try{
        return new TesseractAPI_internal(path, language);
    }catch (const char* err){
        cout << err << endl;
    }
    return nullptr;
}
void TesseractAPI_destroy(TesseractAPI_internal* api){
    delete api;
}




#if 0
char* TesseractAPI_read_file(TesseractAPI_internal* api, const char* filepath){
    TesseractImage image(filepath);
    api->m_api.SetImage(image);
    return api->m_api.GetUTF8Text();
}
#endif

char* TesseractAPI_read_bitmap(
    TesseractAPI_internal* api,
    const unsigned char* data,
    size_t width, size_t height,
    size_t bytes_per_pixel, size_t bytes_per_line,
    size_t ppi
){
    api->m_api.SetImage(data, (int)width, (int)height, (int)bytes_per_pixel, (int)bytes_per_line);
    api->m_api.SetSourceResolution((int)ppi);
    return api->m_api.GetUTF8Text();
}
void Tesseract_delete(char* text){
    delete[] text;
}


