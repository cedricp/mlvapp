#ifndef RAWTOACES_H
#define RAWTOACES_H

#include <vector>
#include <utility>

enum matMethods_t { matMethod0, matMethod1, matMethod2 };
enum wbMethods_t { wbMethod0, wbMethod1, wbMethod2, wbMethod3, wbMethod4 };

struct Option {
    int ret;
    int use_bigfile;
    int use_timing;
    int use_illum;
    int use_mul;
    int use_mmap;
    int msize;
    int verbosity;
    int highlight;
    int get_illums;
    int get_cameras;
    int get_libraw_cameras;

    matMethods_t mat_method;
    wbMethods_t wb_method;

    char * illumType;
    float scale;
    std::vector <std::string> envPaths;

#ifndef WIN32
    void *iobuffer;
#endif

};

class AcesRender {
    public:
        static AcesRender & getInstance();

        void initialize ();
        int preprocessRaw ( const char * path );
        int preprocessRawBuffer(char* buffer, unsigned long buffer_size);
        int postprocessRaw ( );
        void outputACES ( const char*filename, std::vector< std::pair<std::string, std::string >> metadata );
        struct Option& getSettings();
        int fetchIlluminant ( const char * illumType = "na" );

        const std::vector < std::string > getSupportedIllums () const;
        const std::vector < std::string > getSupportedCameras () const;

        void gatherSupportedIllums ();
        void gatherSupportedCameras ();
};



#endif // RAWTOACES_H
