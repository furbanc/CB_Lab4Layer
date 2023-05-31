#!/bin/bash

# header
echo "Extract layers from master projects"

# master project directory
project_path="../project"

# layer output directory
layer_path="../layer"

# intermediate directory
temp_path="temp"

# silent pushd
pushd () {
  command pushd "$@" > /dev/null
}

# silent popd
popd () {
  command popd "$@" > /dev/null
}

# remove intermediate directory if it exists
if [ -d "${temp_path}" ]
then
  rm -r "${temp_path}"
fi

pushd "${layer_path}"

pushd "App"
mkdir "MDK_MW_BSD_Client"
mkdir "MDK_MW_BSD_Server"
mkdir "MDK_MW_FTP_Server"
mkdir "MDK_MW_HTTP_Server"
mkdir "MDK_MW_HTTP_Upload"
mkdir "MDK_MW_SMTP_Client"
mkdir "MDK_MW_SNMP_Agent"
mkdir "MDK_MW_Telnet_Server"
popd

popd

# extract layers from projects
cbuildgen "${project_path}/MDK-Middleware/Network/BSD_Client/MCB4300/BSD_Client.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_BSD_Client"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/BSD_Server/MCB4300/BSD_Server.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_BSD_Server"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/FTP_Server/MCB4300/FTP_Server.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_FTP_Server"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/HTTP_Server/MCB4300/HTTP_Server.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_HTTP_Server"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/HTTP_Upload/MCB4300/HTTP_Upload.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_HTTP_Upload"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/SMTP_Client/MCB4300/SMTP_Client.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_SMTP_Client"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/SNMP_Agent/MCB4300/SNMP_Agent.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_SNMP_Agent"
rm -r "${temp_path}"

cbuildgen "${project_path}/MDK-Middleware/Network/Telnet_Server/MCB4300/Telnet_Server.MCB4300.cprj" extract --outdir="${temp_path}"
rm    "${temp_path}/App/README.md"
cp -r "${temp_path}/App/."    "${layer_path}/App/MDK_MW_Telnet_Server"
rm -r "${temp_path}"

# remove README.md from project (auto generated when projects are composed)
rm "${layer_path}/App/MDK_MW_USBD_HID/README.md"
rm "${layer_path}/App/MDK_MW_USBD_MassStorage/README.md"
