import subprocess
import os
# python scripts for my spring boot application
# Configuration
APP_DIR = '/path/to/your/spring-boot-app'
DOCKER_IMAGE = 'spring-boot-app'
DOCKER_CONTAINER = 'spring-boot-container'

def run_command(command):
    """Run a shell command and print the output."""
    try:
        subprocess.run(command, check=True, shell=True)
        print(f"Command succeeded: {command}")
    except subprocess.CalledProcessError as e:
        print(f"Command failed: {command}\nError: {e}")

def build_docker_image():
    """Build the Docker image."""
    print("Building Docker image...")
    os.chdir(APP_DIR)
    run_command(f'docker build -t {DOCKER_IMAGE} .')

def run_docker_container():
    """Run the Docker container."""
    print("Running Docker container...")
    run_command(f'docker run -d --name {DOCKER_CONTAINER} -p 8080:8080 {DOCKER_IMAGE}')

def run_tests_in_container():
    """Run tests inside the Docker container."""
    print("Running tests in Docker container...")
    run_command(f'docker exec {DOCKER_CONTAINER} mvn test')

def clean_docker_environment():
    """Clean up Docker containers and images."""
    print("Cleaning up Docker environment...")
    run_command(f'docker rm -f {DOCKER_CONTAINER}')
    run_command(f'docker rmi -f {DOCKER_IMAGE}')

def main():
    """Main function to automate Docker tasks."""
    build_docker_image()
    run_docker_container()
    run_tests_in_container()

if __name__ == "__main__":
    main()
