#include "pushConstants.glsl"

#additional_push_constants
{
    uint someIndex1;
    uint someIndex2;
}

#additional_push_constants
{
    uint additionalIndex1;
    uint additionalIndex2;
}

void foo(){
    // some code here
}