FROM ubuntu

LABEL version="1.0" \
      maintainer="thi.hanvan@rapsodo.com" \
      description="This docker setup is used for study linux kernel module development"

# https://dev.to/0xbf/set-timezone-in-your-docker-image-d22 for how to setup timezone
# for timezone list, pls visit https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
ENV TZ=Asia/Singapore

#---------------------------------------------------------------#
# You may change below 4 args to meet your environment
ARG user=thihv-kmoduldev
ARG user_pass=1234
ARG user_id=1000
ARG group_id=1000
#---------------------------------------------------------------#

RUN apt-get update && \
    apt-get install -y sudo && \
    apt-get upgrade -y && \
    useradd --create-home --no-log-init --shell /bin/bash ${user} && \
        adduser ${user} sudo && \
        echo "${user}:${user_pass}" | chpasswd && \
    usermod -u ${user_id} -g ${group_id} ${user} && \
    apt-get clean all

WORKDIR /home/${user}

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
    dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get upgrade -y && \
	apt-get install --show-progress -y build-essential kmod && \
    apt-get clean all

USER ${user}
