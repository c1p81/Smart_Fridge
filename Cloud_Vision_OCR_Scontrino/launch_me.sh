base64 --wrap=0 dettaglio.png > base64.txt
cat ./header.txt ./base64.txt ./footer.txt > test.json
./bash_curl_vision.sh
