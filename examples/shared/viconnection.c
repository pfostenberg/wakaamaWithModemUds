/*******************************************************************************
 *
 * Copyright (c) 2013, 2014 Intel Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v20.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    David Navarro, Intel Corporation - initial API and implementation
 *    Pascal Rieux - Please refer to git log
 *
 *******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "connection.h"
#include "commandline.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

 int Xsendto(int sockfd, const void *buf, size_t len, int flags );



int create_socket(const char * portStr, int addressFamily)
{
    printf("VI: create_socket %s %d\r\n",portStr,addressFamily);
    return 0;
}

connection_t * connection_find(connection_t * connList, struct sockaddr_storage * addr, size_t addrLen)
{
    printf("VI: connection_find \r\n");
    connection_t * connP;

    connP = connList;
    while (connP != NULL)
    {
        if ((connP->addrLen == addrLen)
         && (memcmp(&(connP->addr), addr, addrLen) == 0))
        {
            return connP;
        }
        connP = connP->next;
    }

    return connP;
}

connection_t * connection_new_incoming(connection_t * connList,
                                       int sock,
                                       struct sockaddr * addr,
                                       size_t addrLen)
{
    printf("VI: connection_new_incoming \r\n");
    connection_t * connP;

    connP = (connection_t *)lwm2m_malloc(sizeof(connection_t));
    if (connP != NULL)
    {
        connP->sock = sock;
        memcpy(&(connP->addr), addr, addrLen);
        connP->addrLen = addrLen;
        connP->next = connList;
    }

    return connP;
}

connection_t * connection_create(connection_t * connList,
                                 int sock,
                                 char * host,
                                 char * port,
                                 int addressFamily)
{
    connection_t * connP = NULL;
    printf("VI: connection_create \r\n");
    struct sockaddr sa;
    sa.sa_data[0] = 42;
    sa.sa_data[1] = 0;
    sa.sa_family = AF_INET;


    connP = connection_new_incoming(connList, sock, &sa, sizeof(sa));
    return connP;
}

void connection_free(connection_t * connList)
{
    printf("VI: connection_free \r\n");
    while (connList != NULL)
    {
        connection_t * nextP;

        nextP = connList->next;
        lwm2m_free(connList);

        connList = nextP;
    }
}

int connection_send(connection_t *connP,
                    uint8_t * buffer,
                    size_t length)
{
    printf("VI: connection_send \r\n");
    int nbSent = Xsendto(connP->sock, buffer , length , 0);
    return nbSent;
}



uint8_t lwm2m_buffer_send(void * sessionH,
                          uint8_t * buffer,
                          size_t length,
                          void * userdata)
{
    printf("VI: lwm2m_buffer_send \r\n");
    connection_t * connP = (connection_t*) sessionH;
    //gXconnP = connP;

    (void)userdata; /* unused */

    if (connP == NULL)
    {
        fprintf(stderr, "#> failed sending %zu bytes, missing connection\r\n", length);
        return COAP_500_INTERNAL_SERVER_ERROR ;
    }

    if (-1 == connection_send(connP, buffer, length))
    {
        fprintf(stderr, "#> failed sending %zu bytes\r\n", length);
        return COAP_500_INTERNAL_SERVER_ERROR ;
    }

    return COAP_NO_ERROR;
}

bool lwm2m_session_is_equal(void * session1,
                            void * session2,
                            void * userData)
{
    (void)userData; /* unused */
     printf("VI: lwm2m_session_is_equal \r\n");
    return (session1 == session2);
}
