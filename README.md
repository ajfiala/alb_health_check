This is a healthcheck app that accepts HTTP get requests on port 8080 and responds with a 200 message.
It's intented to be used with the AWS EKS Load Balancer controller https://kubernetes-sigs.github.io/aws-load-balancer-controller/
so that an EC2 load balancer can always be running even while the applications it serves are down or restarting. This reduces the need to 
change DNS mapping to reflect the new ALB URLs every time an application is restarted. 
