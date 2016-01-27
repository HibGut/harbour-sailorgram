#ifndef IMAGESMODEL_H
#define IMAGESMODEL_H


#include <QAbstractListModel>


class ImagesModelWorker;
class QThread;

class ImagesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Role)
    Q_PROPERTY(Role sortRole READ sortRole WRITE setSortRole NOTIFY sortRoleChanged)
    Q_PROPERTY(Qt::SortOrder sortOrder READ sortOrder WRITE setSortOrder NOTIFY sortOrderChanged)
    Q_PROPERTY(bool directoriesFirst READ directoriesFirst WRITE setDirectoriesFirst NOTIFY directoriesFirstChanged)
    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)
    Q_PROPERTY(bool recursive READ recursive WRITE setRecursive NOTIFY recursiveChanged)

public:

    enum Role { PathRole = 0, DateRole = 1, OrientationRole = 2 , UrlRole = 3, IsDirRole = 4, NameRole = 5 };

    struct Entry
    {
        QString path;
        QString name;
        qint64 date;
        int orientation;
        bool isDir;
    };
    typedef QList<Entry> EntryList;

    explicit ImagesModel(QObject *parent = Q_NULLPTR);
    ~ImagesModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    Role sortRole() const { return this->_sortrole; }
    Qt::SortOrder sortOrder() const { return this->_sortorder; }
    bool directoriesFirst() const { return this->_directoriesfirst; }
    QString rootDir() const { return this->_rootdir; }
    bool recursive() const { return this->_recursive; }
    void setSortRole(Role);
    void setSortOrder(Qt::SortOrder);
    void setDirectoriesFirst(bool);
    void setRootDir(const QString&);
    void setRecursive(bool);

signals:

    void sortRoleChanged();
    void sortOrderChanged();
    void directoriesFirstChanged();
    void rootDirChanged();
    void recursiveChanged();
    void dirNeedsScan(QString, QStringList, bool);

private:

    bool lesserThan(const Entry &e1, const Entry &e2, Role role);
    bool biggerThan(const Entry &e1, const Entry &e2, Role role);

    ImagesModelWorker *_worker;
    QThread *_workerthread;
    ImagesModel::EntryList _entries;
    Role _sortrole;
    Qt::SortOrder _sortorder;
    bool _directoriesfirst;
    bool _recursive;
    QString _rootdir;

    static const QStringList _imagesdirpaths;
    static const QStringList _filterlist;

private slots:

    void sort(bool emitReset = true);
    void integrateDirectory(const ImagesModel::EntryList &list, const QString &dirPath);
};

Q_DECLARE_METATYPE(ImagesModel::Entry)


#endif // IMAGESMODEL_H