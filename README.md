# IRProject

git clone https://github.com/Christopherical/IRProject.git

cd IRproject

Run Script to setup venv and run flask:
python3 -m venv .venv
source .venv/bin/activate
pip3 install -r requirements.txt
export FLASK_APP=ransom_api.py
export FLASK_ENV=development

Run Script to build project and periodically run via crontab: 

1. g++ -o ransomProject ransomProject.cpp 
2. echo "1 * * * * cd /home/chronks/Desktop/IRProject && ./ransomProject" | crontab -