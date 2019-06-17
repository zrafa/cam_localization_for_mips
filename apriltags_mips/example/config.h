/* config.h: configuracion para v4l2 y para apriltag_demo camera localization */

//#define FRAME_HEIGHT 120
//#define FRAME_WIDTH 160

/* para v4l2.c */
#define FRAME_HEIGHT 240
#define FRAME_WIDTH  320
#define FRAME_INTERVAL (1000/30)
#define PACK_SIZE 4096 //udp pack size; note that OSX limits < 8100 bytes
#define ENCODE_QUALITY 80

/* para apriltag_demo camera localization */
#define CAM_WIDTH 639	/* lo obtuvo Ale */
#define CAM_HEIGHT 479	/* lo obtuvo Ale */
#define FOCAL_FX 390	/* lo obtuvo Ale 816 */
#define FOCAL_FY 390	/* lo obtuvo Ale 816 */
#define TAGSIZE 0.05	/* en centimetros */
