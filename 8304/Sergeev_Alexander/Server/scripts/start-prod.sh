

# sudo forever start -o logs/log.log -e logs/err.log dist/index.js

firewall-cmd --zone=public --add-port=1109/tcp --permanent

firwall-cmd --reload