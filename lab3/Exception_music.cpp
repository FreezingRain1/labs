#include "Exception_music.h"

wavExc::wavExc( const std::string &message ) noexcept : message( message ) {}
wavExc::~wavExc() noexcept {}
const char* wavExc::what() const noexcept {
	
    return message.c_str();
}
io_Error::io_Error( const std::string &message ) noexcept : wavExc( message ) {}

header_Bytes_Rate_Error::header_Bytes_Rate_Error( const std::string &message ) noexcept : wavExc( message ) {}

header_Fmt_Error::header_Fmt_Error( const std::string &message ) noexcept : wavExc( message ) {}

header_Riff_Error::header_Riff_Error( const std::string &message ) noexcept : wavExc( message ) {}

bad_Params::bad_Params( const std::string &message ) noexcept : wavExc( message ) {}

header_Wave_Error::header_Wave_Error( const std::string &message ) noexcept : wavExc( message ) {}

bad_Format::bad_Format( const std::string &message ) noexcept : wavExc( message ) {}

header_Subchunk2_Error::header_Subchunk2_Error( const std::string &message ) noexcept : wavExc( message ) {}

header_Subchunkl_Error::header_Subchunkl_Error( const std::string &message ) noexcept : wavExc( message ) {}

header_Not_Pcm::header_Not_Pcm( const std::string &message ) noexcept : wavExc( message ) {}

header_Block_Align_Error::header_Block_Align_Error( const std::string &message ) noexcept : wavExc( message ) {}





