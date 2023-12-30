import tensorflow as tf
import numpy as np
import cv2
import time
import serial

# Load the trained model
model = tf.keras.models.load_model('/home/pi/Desktop/imageclassifier.h5')

# Define the class labels
class_labels = ['Null','Paper','Polythene','Wastefood',]

# Load and preprocess the image
def preprocess_image(image):
    #image = cv2.cvtColor(cv2.imread(image),cv2.COLOR_BGR2RGB)
    image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
    image = tf.image.resize(image, (256,256))  # Resize to match the input size of the model
    image = tf.cast(image, tf.float32) / 255.0
    #image = image.astype('float32') / 255.0  # Normalize the pixel values
    image = np.expand_dims(image, axis=0)  # Add batch dimension
    return image

# Capture and classify a single photo
def classify_photo():
    # Open the video capture
    cap = cv2.VideoCapture(0)

    # Set up Arduino serial communication
    arduino = serial.Serial('/dev/ttyACM0', 9600)  # Replace with the correct port and baud rate

    while True:
        # Read a frame from the video capture
        ret, frame = cap.read()

        # Display the frame
        cv2.imshow('Camera', frame)

        # Check for incoming signal from Arduino
        if arduino.in_waiting > 0:
            signal = arduino.readline().decode().strip()
            print(signal)
            if signal == 'STOP':
                # Stop the conveyor belt
                time.sleep(2)

                # Capture photo
                # Preprocess the captured photo
                preprocessed_frame = preprocess_image(frame)

                # Make predictions
                predictions = model.predict(preprocessed_frame)
                predicted_class = np.argmax(predictions)
                class_label = class_labels[predicted_class]

                # Display the predicted class on the frame
                cv2.putText(frame, class_label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
                cv2.imshow('Classification', frame)

                # Send the class label to Arduino
                arduino.write(class_label.encode())

                # Wait for 2 seconds
                time.sleep(2)

                # Start the conveyor belt
                #arduino.write(b'START\n')

        # Exit if 'q' is pressed
        if cv2.waitKey(1) == ord('q'):
            break

    # Release the video capture
    cap.release()
    cv2.destroyAllWindows()

# Start capturing and classifying photos
classify_photo()

