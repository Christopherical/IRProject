from flask import Flask 
app = Flask(__name__)

@app.route('/')
def index():
	return "hello"

@app.route('/testGet')
def get_test():
	return {"fish": "marlin"}