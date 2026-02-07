FROM debian:bookworm

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libreadline-dev \
    valgrind \
    bash \
    && rm -rf /var/lib/apt/lists/*

# Working directory
WORKDIR /Minishell

# Copy project
COPY . .

## build image:
	# docker build -t minishell .
## run bash inside image:
	# docker run -it --rm minishell
	# or
	# docker run -it --rm --env TERM=xterm minishell

## to clean image
	# docker image rm minishell:latest