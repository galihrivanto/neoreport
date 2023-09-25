#ifndef Q_NCREPORT_ENGINE_H
#define Q_NCREPORT_ENGINE_H 

#include <qapplication.h>
#include <qobject.h>

namespace neoreport::engine
{
    class QWorker : public QObject
    {
        Q_OBJECT

        public:
            QWorker(
                QString template_path,
                QString output_path,
                QString zint_dir,
                core::OutputFormat output_format
            ) : 
            m_template_path(template_path),
            m_output_path(output_path),
            m_zint_dir(zint_dir),
            m_format(output_format) {}

            ~QWorker();

        public slots:
            void process();
        
        signals:
            void progress(QString message);
            void finished();
            void error(QString err);

        private:
            QString m_template_path;
            QString m_output_path;
            QString m_zint_dir;
            core::OutputFormat m_format;     
    };

    class QManager : public QObject {
        Q_OBJECT 

        public:
            QManager() :  m_app(nullptr) {
                int argc;
                m_app = new QApplication(argc, nullptr);
            }
            ~QManager() {
                delete m_app;
            }

        core::Response generate(QString zint_dir, QString template_path, QString output_path, core::OutputFormat format);            
    
        private:
            QApplication* m_app;
    };
}

#endif 