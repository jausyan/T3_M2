# Estimated aircraft displacement for one frame (what gets POSTed to the server)
std_msgs/Header header
int64 frame_index
string frame_url
float64 x                  # metres, relative to first frame of the session
float64 y
float64 z
