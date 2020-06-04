# for future
setx NODE_PATH %AppData%/npm/node_modules
# for current session
set NODE_PATH=%AppData%/npm/node_modules

set GYP_MSVS_VERSION=2019

npm config set msvs_version 2019 --global