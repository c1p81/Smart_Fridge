#!/bin/bash

# modificato da originale di Google da Luca Innocenti
# funziona su piattaforma Linux Debian testing

# Copyright 2017 Google Inc.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# crea il file JSON con il file audio codificato in BASE64
FILENAME="request-"`date +"%s".json`
cat <<EOF > $FILENAME
{
  "config": {
    "encoding":"FLAC",
    "profanityFilter": true,
    "languageCode": "it-IT",
    "speechContexts": {
      "phrases": ['']
    },
    "maxAlternatives": 1
  },
  "audio": {
    "content":
	}
}
EOF

# Update the languageCode parameter if one was supplied
if [ $# -eq 1 ]
  then
    sed -i '' -e "s/it-IT/$1/g" $FILENAME
fi

# qui sono stati modificati dei parametri rispetto all'esempio originale
read -p "Press enter when you're ready to record" rec
if [ -z $rec ]; then
  rec --channels=1 audio.flac trim 0 1.5

  echo \"`base64 --wrap=0 audio.flac`\" > audio.base64
  sed -i '' -e '/"content":/r audio.base64' $FILENAME
fi

# Chiamata 1  alle API Speech to text 
curl -s -X POST -H "Content-Type: application/json" --data-binary @${FILENAME} -H "apikey: xxxxxxxxxxxxxxxxxxxxxxx"  https://hackathon.tim.it/gcloudspeechtotext/v1/speech:longrunningrecognize > step1.json

# legge il file json di risposta e trimma i quotation marks
step1=$(jq .name step1.json)
temp="${step1%\"}"
temp="${temp#\"}"

# questa pausa e' necessaria non rimuovere
sleep 3
#echo "Traduzione"

curl -s -H "Content-Type: application/json" -H "apikey: xxxxxxxxxxxxxxxxxxxxxxxxxx" "https://hackathon.tim.it/gcloudspeechtotext/v1/operations/$temp"  > traduzione.json

echo "Testo"
jq -r '.response.results[0].alternatives[0].transcript' traduzione.json
