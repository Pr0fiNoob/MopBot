from mopsloth import app
from time import *

while True:
    try:
        # Your main application logic here
        pass
    except Exception as e:
        print(f"An error occurred: {e}")
        # Optionally, you can add a sleep here to avoid rapid retries
        time.sleep(1)

