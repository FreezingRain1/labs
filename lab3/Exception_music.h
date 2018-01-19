#ifndef EXCEPTION_MUSIC_H_INCLUDED
#define EXCEPTION_MUSIC_H_INCLUDED

#include <exception>
#include <stdexcept>

using namespace std;

class wavExc : public exception {
public:
    wavExc( const string &message ) noexcept ;
    ~wavExc () noexcept ;
    const char* what() const noexcept override;
private:
    string message ;
};

class io_Error : public wavExc {
public:
    io_Error( const std::string &message ) noexcept ;
};
class bad_Format : public wavExc {
public:
    bad_Format( const std::string &message ) noexcept ;
};
class header_Riff_Error : public wavExc {
public:
    header_Riff_Error( const std::string &message ) noexcept ;
};
class header_Wave_Error : public wavExc {
public:
    header_Wave_Error( const std::string &message ) noexcept ;
};
class header_Fmt_Error : public wavExc {
public:
    header_Fmt_Error( const std::string &message ) noexcept ;
};
class header_Not_Pcm : public wavExc {
public:
    header_Not_Pcm( const std::string &message ) noexcept ;
};
class header_Subchunkl_Error : public wavExc {
public:
    header_Subchunkl_Error( const std::string &message ) noexcept ;
};
class header_Bytes_Rate_Error : public wavExc {
public:
    header_Bytes_Rate_Error( const std::string &message ) noexcept ;
};
class header_Block_Align_Error : public wavExc {
public:
    header_Block_Align_Error( const std::string &message ) noexcept ;
};
class header_Subchunk2_Error : public wavExc {
public:
    header_Subchunk2_Error( const std::string &message ) noexcept ;
};
class bad_Params : public wavExc {
public:
    bad_Params( const std::string &message ) noexcept ;
};


#endif // EXCEPTION_MUSIC_H_INCLUDED
