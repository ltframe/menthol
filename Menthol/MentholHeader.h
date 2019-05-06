#ifndef MentholHeader
#define MentholHeader
#include "../Menthol/Menthol.h"
#ifdef _DEBUG
#pragma comment(lib,"../debug/menthol.lib")
#else
#pragma comment(lib,"../release/menthol.lib")
#endif
#endif
