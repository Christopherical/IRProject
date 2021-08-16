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

Run Script to build project and periodically run via crontab: 
1. sudo apt-get install nlohmann-json3-dev
2. g++ -std=c++11 ransomProject.cpp ransomFunctions.cpp -o ransomProject
3. echo "* * * * * cd /home/chronks/Desktop/IRProject && ./ransomProject" | crontab -

Docs:
https://json.nlohmann.me/api/basic_json/parse/
Testd