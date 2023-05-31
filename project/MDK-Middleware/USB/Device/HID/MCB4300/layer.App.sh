# Update MDK-Middleware USB Device configuration files based on provided interface settings described in the board layer
sed -i "s/USBD0_PORT        *[^ ]*/USBD0_PORT                      $CMSIS_USBD_PORT/"        "RTE/USB/USBD_Config_0.c"
if [ ! -z ${CMSIS_USBD_SPEED} ]; then
sed -i "s/USBD0_HS          *[^ ]*/USBD0_HS                        $CMSIS_USBD_SPEED/"       "RTE/USB/USBD_Config_0.c"
fi
if [ ! -z ${CMSIS_USBD_MAX_PACKET0} ]; then
sed -i "s/USBD0_MAX_PACKET0 *[^ ]*/USBD0_MAX_PACKET0               $CMSIS_USBD_MAX_PACKET0/" "RTE/USB/USBD_Config_0.c"
fi
