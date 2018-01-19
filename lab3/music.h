#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "Exception_music.h"
#include <vector>
#include "music.h"
#include<stdio.h>
#include<stdint.h>

using namespace std;

struct wav_header
{
    __int32 chunkId;
    uint32_t chunkSize;
    __int32 format;
    __int32 subchunk1Id;
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    __int32 subchunk2Id;
    uint32_t subchunk2Size;
};

class Music {
public:
    Music()
	{
  	
	}
    void read_Header( const char* file_name, wav_header* header_ptr ) {
    cout << "Reads file and puts header's data" <<endl;
    null_Header( header_ptr);
    FILE* f = fopen( file_name, "rb" );
    if ( !f ) {
        throw io_Error( "File is not exist" );
    }
    size_t blocks_read = fread( header_ptr, sizeof( wav_header ), 1, f);
    if ( blocks_read != 1 ) {
        throw bad_Format( "Can't read header, because the file is too small." );
    }
    fseek( f, 0, SEEK_END );
    size_t file_size = ftell( f );
    fclose( f );
    check_Header( header_ptr, file_size );
	} 
	

    void print_Info( const wav_header* header_ptr ) {
    cout <<"__________________________________________"<<endl; 
    cout <<" audioFormat   "<< header_ptr -> audioFormat <<endl;
    cout <<" numChannels   "<< header_ptr -> numChannels <<endl;
    cout <<" sampleRate    "<< header_ptr -> sampleRate <<endl;
    cout <<" bitsPerSample "<< header_ptr -> bitsPerSample<<endl;
    cout <<" byteRate      "<< header_ptr -> byteRate<<endl;
    cout <<" blockAlign    "<< header_ptr -> blockAlign<<endl;
    cout <<" chunkSize     "<< header_ptr -> chunkSize<<endl;
    cout <<" subchunk1Size "<< header_ptr -> subchunk1Size<<endl;
    cout <<" subchunk2Size "<< header_ptr -> subchunk2Size<<endl;
    cout <<"__________________________________________"<<endl;}
	
    void make_Wav_File( const char* file_name, int sample_rate, std::vector<std::vector<short>>& channels_data ) {
    cout <<"> make_wav_file"<< file_name_o <<endl;
    int chan_count = (int)channels_data.size();

    if ( chan_count < 1 ) {
        throw bad_Params( "Bad params" );
    }

    int samples_count_per_chan = (int)channels_data[0].size();

    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( channels_data[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw bad_Params( "Bad params" );
        }
    }

    fill_Header( &header, chan_count, 16, sample_rate, samples_count_per_chan );

    vector<short> all_channels;
    all_channels.resize( chan_count * samples_count_per_chan );

    for ( int ch = 0; ch < chan_count; ch++ ) {
        const std::vector<short>& chdata = channels_data[ ch ];
        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            all_channels[ chan_count * i + ch ] = chdata[ i ];
        }
    }

    FILE* f = fopen( file_name_o, "wb" );
    fwrite( &header, sizeof(wav_header), 1, f );
    fwrite( all_channels.data(), sizeof(short), all_channels.size(), f );
    if ( !f ) {
            throw io_Error( "IO error" );
    }

    fclose( f );
	}

    void make_Mono( const std::vector<std::vector<short> > &channels_data, std::vector< std::vector<short> > &edited_data ){
    int chan_count = (int)channels_data.size();

    if ( chan_count != 2 ) {
        throw bad_Params( "Bad params" );
    }

    int samples_count_per_chan = (int)channels_data[0].size();

    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( channels_data[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw bad_Params( "Bad params" );
        }
    }

    edited_data.resize( 1 );
    vector<short>& mono = edited_data[ 0 ];
    mono.resize( samples_count_per_chan );

    for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
        mono[ i ] = ( channels_data[0][i] + channels_data[1][i] ) / 2;
    }
	}
	
    void make_Reverb( std::vector<std::vector<short>>& edited_data, int sample_rate, double delay_seconds, float decay ) {
    int chan_count = (int)edited_data.size();

    if ( chan_count < 1 ) {
        throw bad_Params( "Bad params" );
    }

    int samples_count_per_chan = (int)edited_data[0].size();

    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        if ( edited_data[ ch ].size() != (size_t) samples_count_per_chan ) {
            throw bad_Params( "Bad params" );
        }
    }

    int delay_samples = (int)(delay_seconds * sample_rate);


    for ( size_t ch = 0; ch < chan_count; ch++ ) {
        vector<float> tmp;
        tmp.resize(edited_data[ch].size());

        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            tmp[ i ] = edited_data[ ch ][ i ];
        }

        for ( size_t i = 0; i < samples_count_per_chan - delay_samples; i++ ) {
            tmp[ i + delay_samples ] += decay * tmp[ i ];
        }

        float max_magnitude = 0.0f;
        for ( size_t i = 0; i < samples_count_per_chan - delay_samples; i++ ) {
            if ( abs(tmp[ i ]) > max_magnitude ) {
                max_magnitude = std::abs(tmp[ i ]);
            }
        }

        float norm_coef = 30000.0f / max_magnitude;
        cout<<"max_magnitude = "<< max_magnitude<<endl;
		cout<<"coef = "<< norm_coef <<endl;

        for ( size_t i = 0; i < samples_count_per_chan; i++ ) {
            edited_data[ ch ][ i ] = (short)(norm_coef * tmp[ i ]);
        }
    }
	}
	
    void extract_data_int16( const char* file_name, std::vector<std::vector<short>>& channels_data ) {
    cout<<"> extract_data_int16"<< file_name <<endl;
    read_Header( file_name, &header );

    if ( header.bitsPerSample != 16 ) {
        throw bad_Format( "Unsupported format" );
    }

    FILE* f = fopen( file_name, "rb" );
    if ( !f ) {
        throw io_Error( "Io error" );
    }
    fseek( f, 44, SEEK_SET );

    int chan_count = header.numChannels;
    int samples_per_chan = ( header.subchunk2Size / sizeof(short) ) / chan_count;

    vector<short> all_channels;
    all_channels.resize( chan_count * samples_per_chan );
    size_t read_bytes = fread( all_channels.data(), 1, header.subchunk2Size, f );
    if ( read_bytes != header.subchunk2Size ) {
        cout<< "extract_data_int16() read only"<< read_bytes<< " of " << header.subchunk2Size <<endl;
        throw io_Error( "Io error" );
    }
    fclose( f );

    channels_data.resize( chan_count );
    for ( size_t ch = 0; ch < channels_data.size(); ch++ ) {
        channels_data[ ch ].resize( samples_per_chan );
    }

    for ( int ch = 0; ch < chan_count; ch++ ) {
        vector<short>& chdata = channels_data[ ch ];
        for ( size_t i = 0; i < samples_per_chan; i++ ) {
            chdata[ i ] = all_channels[ chan_count * i + ch ];
        }
    }
	}	



private:
    void check_Header( const wav_header* header_ptr, size_t file_size_bytes ) {
    if ( header_ptr -> chunkId != 0x46464952 ) {
        throw header_Riff_Error( " Header riff error" );
    }

    if ( header_ptr -> chunkSize != file_size_bytes - 8 ) {
        throw header_Riff_Error( " Header riff size error" );
    }

    if ( header_ptr -> format != 0x45564157 ) {
        throw header_Wave_Error( "Header wave error" );
    }

    if ( header_ptr -> subchunk1Id != 0x20746d66 ) {
        throw header_Fmt_Error( "Header fmt error" );
    }

    if ( header_ptr -> audioFormat != 1 ) {
        throw header_Not_Pcm( "Header not pcm" );
    }

    if ( header_ptr -> subchunk1Size != 16 ) {
        throw header_Subchunkl_Error( "Header subchunkl error" );
    }

    if ( header_ptr -> byteRate != header_ptr -> sampleRate * header_ptr -> numChannels * header_ptr -> bitsPerSample / 8 ) {
        throw header_Bytes_Rate_Error( "Header bytes rate error" );
    }

    if ( header_ptr -> blockAlign != header_ptr -> numChannels * header_ptr -> bitsPerSample / 8 ) {
        throw header_Block_Align_Error( "Header block align error" );
    }

    if ( header_ptr -> subchunk2Id != 0x61746164 ) {
        throw header_Fmt_Error( "Header fmt error" );
    }

    if ( header_ptr -> subchunk2Size != file_size_bytes - 44 ) {
        throw header_Subchunk2_Error( "Header subchunk2 size error" );
    }
    }
    
    void null_Header( wav_header *header_ptr ) {
    memset( header_ptr, 0, sizeof( wav_header ) );
	}

    void prefill_Header( wav_header* header_ptr ) {
    header_ptr -> chunkId = 0x46464952;
    header_ptr -> format = 0x45564157;
    header_ptr -> subchunk2Id = 0x61746164;
    header_ptr -> audioFormat = 1;
    header_ptr -> subchunk1Size = 16;
    header_ptr -> bitsPerSample = 16;}

	void fill_Header( wav_header* header_ptr, int chan_count, int bits_per_sample, int sample_rate, int samples_count_per_chan ) {
    if ( bits_per_sample != 16 ) {
        throw bad_Format( "Unsupported format" );
    }

    if ( chan_count < 1 ) {
        throw bad_Params( "Bad params" );
    }
    prefill_Header( header_ptr );

    int file_size_bytes = 44 + chan_count * ( bits_per_sample / 8 ) * samples_count_per_chan;

    header_ptr -> sampleRate    = sample_rate;
    header_ptr -> numChannels   = chan_count;
    header_ptr -> bitsPerSample = 16;

    header_ptr -> chunkSize     = file_size_bytes - 8;
    header_ptr -> subchunk2Size = file_size_bytes - 44;

    header_ptr -> byteRate      = header_ptr -> sampleRate * header_ptr -> numChannels * header_ptr -> bitsPerSample / 8;
    header_ptr -> blockAlign    = header_ptr -> numChannels * header_ptr -> bitsPerSample / 8;
    }

protected:
    vector< vector<short> > channels_data;
    vector< vector<short> > edited_data;
    wav_header header;
    const char* file_name;
    const char* file_name_o;
};

#endif // MUSIC_H_INCLUDED

