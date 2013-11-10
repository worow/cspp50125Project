
#include "Messages.h"


#define ME_TB_TR_SHM_KEY 0x1234 /*Shared Mem between ME, trade reporter and trade publisher*/
#define ME_BP_SHM_KEY 0x5678 /*Shared Mem between ME and book publisher */

#define ME_BP_SEM_KEY 0x4321 /*Sem Key between ME and Book publisher */
#define ME_TP_SEM_KEY 0x8765 /*Sem key between ME and Trade publisher */
#define ME_TR_SEM_KEY 0x4725 /*Sem key between ME and Trade Reporter */

#define ME_TO_CM_QUE_KEY 0x3333 /*Msq queue that ME writes to and ConMan reads from*/
#define CM_TO_ME_QUE_KEY 0x7777 /*Msg queue that ConMan writes to and ME reads from*/


#define numSemaphoresForTradeSharedMemory 2
#define numSemaphoresForBookStateSharedMemory 1

#define sizeInBytesTradeMessage sizeof(struct TradeMessage)
#define sizeInBytesBookStateMessage sizeof(struct BookMessage)

const char* IP_ADDR = "239.192.03.03"; /*IP address for multicast bus*/
const char* PORT = "1234"; /*Port for multicast Bus*/

