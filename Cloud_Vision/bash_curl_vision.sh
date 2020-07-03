curl -s -X POST -H "Content-Type: application/json" --data-binary @test.json -H "apikey: xxxxxxxxxxxxxxxxxxxxxxxxxxx"  https://hackathon.tim.it/gcloudvision/v1/images:annotate > risultato.json
sleep 3
jq .responses[0].labelAnnotations[0].description risultato.json
