
RED='\033[0;31m'
NC='\033[0m'

echo -e "${RED}COMPILING SERVER....\n${NC}"
(cd ./server && make)

echo -e "${RED}COMPILING CLIENTS...\n${NC}" 
(cd ./clients && make)