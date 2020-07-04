curl -s -X POST -H "Content-Type: application/json" --data-binary @./test.json -H "apikey: xxxxxxxxxxxxxxxxxxxxxxxxxxxx"  https://hackathon.tim.it/gcloudvision/v1/images:annotate > risultato.json
sleep 3
jq .responses[0].textAnnotations[0].description risultato.json
