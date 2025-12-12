from flask import Flask, jsonify

from dataparser import lines_parser as lp

app = Flask(__name__)


@app.route("/")
def home():
    return "Hello World!"


@app.route("/typing")
def typing():
    line = lp()
    return jsonify({"text": line})


if __name__ == "__main__":
    app.run()
