# IRProject

git clone https://github.com/Christopherical/IRProject.git

cd IRproject

Run Script to setup venv and run flask:
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt
export FLASK_APP=ransom_api.py
export FLASK_ENV=development
flask run

Run start script ./ransomStart.sh to run the program once and add a periodic job to the crontab every minute which encrypts any new files.

Run stop scrupt ./ransomStop/.sh to run a program which decrypts the already encrypted files and removes the crontab job.

Library Repo/Docs:
https://json.nlohmann.me/api/basic_json/parse/
https://github.com/elnormous/HTTPRequest
