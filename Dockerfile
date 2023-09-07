# Use an official base image
FROM gcc:latest

# Set the working directory
WORKDIR /usr/src/app

# Copy all source files
COPY . .

# Use Makefile to compile the C application
RUN make

# Run the application
CMD ["./healthcheck_app"]
