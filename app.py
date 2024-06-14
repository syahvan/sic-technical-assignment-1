from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

# Route untuk halaman utama
@app.route('/')
def index():
    return render_template('index.html')

# Route untuk menerima data dari ESP32
@app.route('/data', methods=['POST'])
def receive_data():
    data = request.get_json()
    distance = data.get('distance')
    
    if distance:
        response = {
            "status": "success",
            "message": f"Distance received: {distance} cm"
        }
    else:
        response = {
            "status": "failed",
            "message": "No distance data received"
        }
    
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
