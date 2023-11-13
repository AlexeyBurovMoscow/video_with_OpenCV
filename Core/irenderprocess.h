#ifndef IRENDERPROCESS_H
#define IRENDERPROCESS_H

#include <QImage>

namespace Interface {

    //base image render process
    class IRenderProcess {

    public:

        //work with image here
        virtual void imageProcessing(QImage& image) = 0;
    };
}

#endif // IRENDERPROCESS_H
