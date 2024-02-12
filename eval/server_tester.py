import socket
import subprocess
import time
import os
import inspect

host = '127.0.0.1'
port = 2021
client_socket = None

marks = 0

def print_passed(msg):
    print("\033[92m" + msg + "\033[0m")


def print_failed(msg):
    print("\033[91m" + msg + "\033[0m")

def init_client():
    global client_socket

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.settimeout(1)

    subprocess.Popen("gcc ../impl/server.c -o ../impl/server && ../impl/server {} {}".format(host, port), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    time.sleep(3)
    try:
        client_socket.connect((host, port))
    except:
        print_failed("init_client - TEST CASE FAILED")
        return 0
    print_passed("init_client - TEST CASE PASSED")
    return 1


def test_server_greater_than_or_equal_to_5_characters():
    message = "test123"
    client_socket.sendall(message.encode())
    data = client_socket.recv(1024).decode()
    if data != message:
        print_failed("test_server_greater_than_or_equal_to_5_characters - TEST CASE FAILED")
        return 0
    else:
        print_passed("test_server_greater_than_or_equal_to_5_characters - TEST CASE PASSED")
        return 1

def test_server_less_than_5_characters():
    message = "test"
    client_socket.sendall(message.encode())
    data = client_socket.recv(1024).decode()
    expected = "Error: Message length must be more than 5 characters"
    if data != expected:
        print_failed("test_server_less_than_5_characters - TEST CASE FAILED")
        return 0
    else:
        print_passed("test_server_less_than_5_characters - TEST CASE PASSED")
        return 1

def eval():
    marks = 0
    marks += init_client()
    marks += test_server_greater_than_or_equal_to_5_characters()
    marks += test_server_less_than_5_characters()

    print("Marks: ", marks)
    return marks

if __name__ == "__main__":
    current_script_path = inspect.getfile(inspect.currentframe())
    directory = os.path.dirname(current_script_path)
    os.chdir(directory)
    try:
        eval()
    except:
        print_failed("Script crashed while Testing, Test Case Failed")

