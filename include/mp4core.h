/*****************************************************************************                          
  Copyright (C) 2018 Fillet                                                                             
                                                                                                        
  This program is free software; you can redistribute it and/or modify                                  
  it under the terms of the GNU General Public License as published by                                  
  the Free Software Foundation; either version 2 of the License, or                                     
  (at your option) any later version.                                                                   
                                                                                                        
  This program is distributed in the hope that it will be useful,                                       
  but WITHOUT ANY WARRANTY; without even the implied warranty of                                        
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                         
  GNU General Public License for more details.                                                          
                                                                                                        
  You should have received a copy of the GNU General Public License                                     
  along with this program; if not, write to the Free Software                                           
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111, USA.                             
                                                                                                        
  This program is also available under a commercial license with                                        
  customization/support packages and additional features.  For more                                     
  information, please contact us at cannonbeachgoonie@gmail.com                                         
                                                                                                        
******************************************************************************/

#if !defined(_MP4CORE_H_)
#define _MP4CORE_H_

#define TRACK_TYPE_VIDEO    0x00
#define TRACK_TYPE_AUDIO    0x01
#define TRACK_TYPE_CAPTION  0x02
#define MAX_TRACKS          16

#define MAX_NAME_SIZE       512
#define MAX_MP4_SIZE        16384*1024

#define MEDIA_TYPE_AAC      0x01
#define MEDIA_TYPE_AC3      0x02
#define MEDIA_TYPE_EAC3     0x03

#define MEDIA_TYPE_H264     0x10
#define MEDIA_TYPE_HEVC     0x11

#define MAX_FRAGMENTS       20*60    // 60 fps @ 20 seconds
#define MAX_PRIVATE_DATA_SIZE  256
#define MAX_AUDIO_CONFIG_SIZE  16

typedef struct _fragment_struct_
{
    uint8_t                 *fragment_buffer;
    int                     fragment_buffer_size;
    int                     fragment_duration;
    double                  fragment_timestamp;
    int64_t                 fragment_composition_time;
} fragment_struct;

typedef struct _fragment_file_struct_
{
    char                   fragment_filename[MAX_NAME_SIZE];
    FILE                   *output_file;

    int                    media_type;
    int                    track_count;
    int                    track_type;
    int                    timescale;
    int64_t                sequence_number;
    int                    frag_duration;
    int                    total_duration;

    int                    video_width;
    int                    video_height;
    int                    video_bitrate;
    uint8_t                video_sps[MAX_PRIVATE_DATA_SIZE];
    int                    video_sps_size;
    uint8_t                video_pps[MAX_PRIVATE_DATA_SIZE];
    int                    video_pps_size;
    uint8_t                video_vps[MAX_PRIVATE_DATA_SIZE];
    int                    video_vps_size;

    int                    audio_channels;
    int                    audio_samplerate;
    int                    audio_bitrate;
    int                    audio_object_type;
    uint32_t               audio_config;
    int                    audio_config_size;
    int                    subtitle_bitrate;
    int                    lang_code;

    int                    next_track_id;
    int                    track_id;

    int64_t                sidx_buffer_offset;
    int64_t                duration_buffer_offset;

    int64_t                buffer_offset;
    int64_t                initial_offset;
    uint8_t                *buffer;

    fragment_struct        fragments[MAX_FRAGMENTS];
    int                    fragment_count;
    int64_t                fragment_start_timestamp;
} fragment_file_struct;

int fmp4_audio_fragment_add(fragment_file_struct *fmp4,
			    uint8_t *fragment_buffer,
			    int fragment_buffer_size,
			    double fragment_timestamp,
			    int fragment_duration);

int fmp4_video_fragment_add(fragment_file_struct *fmp4,
			    uint8_t *fragment_buffer,
			    int fragment_buffer_size,
			    double fragment_timestamp,
			    int fragment_duration,
			    int64_t fragment_composition_time);

fragment_file_struct *fmp4_file_create(int media_type, int timescale, int lang_code, int frag_duration);
int fmp4_file_finalize(fragment_file_struct *fmp4);
int fmp4_fragment_start(fragment_file_struct *fmp4);
int fmp4_fragment_end(fragment_file_struct *fmp4);
int fmp4_video_set_pps(fragment_file_struct *fmp4, uint8_t *pps, int pps_size);
int fmp4_video_set_sps(fragment_file_struct *fmp4, uint8_t *sps, int sps_size);
int fmp4_video_set_vps(fragment_file_struct *fmp4, uint8_t *vps, int vps_size);
int fmp4_output_header(fragment_file_struct *fmp4);
uint8_t *fmp4_get_fragment(fragment_file_struct *fmp4, int *fragment_size);
int fmp4_video_track_create(fragment_file_struct *fmp4, int video_width, int video_height, int video_bitrate);
int fmp4_audio_track_create(fragment_file_struct *fmp4, int audio_channels, int audio_samplerate, int audio_object_type, int audio_bitrate);


#endif // _MP4CORE_H_
