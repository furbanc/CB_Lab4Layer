# Update MDK-Middleware USB Device configuration files based on provided interface settings described in the board layer
sed -i "s/USBD0_PORT        *[^ ]*/USBD0_PORT                      $CMSIS_USBD_PORT/"        "RTE/USB/USBD_Config_0.c"
if [ ! -z ${CMSIS_USBD_SPEED} ]; then
sed -i "s/USBD0_HS          *[^ ]*/USBD0_HS                        $CMSIS_USBD_SPEED/"       "RTE/USB/USBD_Config_0.c"
fi
if [ ! -z ${CMSIS_USBD_MAX_PACKET0} ]; then
sed -i "s/USBD0_MAX_PACKET0 *[^ ]*/USBD0_MAX_PACKET0               $CMSIS_USBD_MAX_PACKET0/" "RTE/USB/USBD_Config_0.c"
fi

# Update MDK-Middleware File System configuration files based on provided interface settings described in the board layer
sed -i "s/MC0_MCI_DRIVER    *[^ ]*/MC0_MCI_DRIVER          $CMSIS_MCI_DRIVER/"     "RTE/File_System/FS_Config_MC_0.h"
if [ ! -z ${CMSIS_MCI_CACHE_ADDR} ]; then
sed -i "s/MC0_CACHE_RELOC   *[^ ]*/MC0_CACHE_RELOC         1/"                     "RTE/File_System/FS_Config_MC_0.h"
sed -i "s/MC0_CACHE_ADDR    *[^ ]*/MC0_CACHE_ADDR          $CMSIS_MCI_CACHE_ADDR/" "RTE/File_System/FS_Config_MC_0.h"
fi
