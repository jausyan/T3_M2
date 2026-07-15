# One competition frame as received from the server (Figure 16 of the guidebook)
std_msgs/Header header
int64 frame_index          # 0-based index in the session
string frame_url           # unique url of the frame ("url" field)
string video_name
string session
float64 ref_x              # translation_x from server (0.0 when invalid)
float64 ref_y              # translation_y from server
float64 ref_z              # translation_z from server
bool ref_valid             # false when server sent "NaN" / health_status == 0
int8 health_status         # 1 = position system healthy, 0 = unhealthy
sensor_msgs/Image image    # the decoded camera frame
