from flask import Flask, request 
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)


app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///data.db'
db = SQLAlchemy(app)


class Location(db.Model):
	id = db.Column(db.Integer, primary_key=True)
	file_location = db.Column(db.String(240), unique=True, nullable=False)
	def __repr__(self):
		return f"{self.file_location}"


@app.route('/')
def index():
	return "Locations Home"


#Get request for locations.
@app.route('/locations')
def get_locations():
	locations = Location.query.all()
	if locations is None:
		return {"error": "not found"}

	output = []
	for location in locations:
		location_data = {'location': location.file_location}
		output.append(location_data)
	return{"locations": output}


#Get specific location.
@app.route('/locations/<id>')
def get_location(id):
	location = Location.query.get_or_404(id)
	if location is None:
		return {"error": "not found"}
	return {"location": location.file_location}	


#Post request to add locations.
@app.route('/locations', methods=['POST'])
def add_location():
	location = Location(file_location=request.json['file_location'])
	db.session.add(location)
	db.session.commit()
	return {'id': location.id}


#Delete request to remove locations.
@app.route('/locations/<id>', methods=['DELETE'])
def delete_location(id):
	location = Location.query.get(id)
	if location is None:
		return {"error": "not found"}

	db.session.delete(location)
	db.session.commit()
	return {"message": "deleted"}

#TODO - USE RSA Encryption Algorithm.
#Get request secret_key.
@app.route('/secretKey')
def get_secret_key():	
	rsa_d = 11
	
	return{"rsa_d": rsa_d}