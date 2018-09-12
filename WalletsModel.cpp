#include "WalletsModel.h"

WalletsModel::WalletsModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant WalletsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	// FIXME: Implement me!
}

QModelIndex WalletsModel::index(int row, int column, const QModelIndex &parent) const
{
	// FIXME: Implement me!
}

QModelIndex WalletsModel::parent(const QModelIndex &index) const
{
	// FIXME: Implement me!
}

int WalletsModel::rowCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return 0;

	// FIXME: Implement me!
}

int WalletsModel::columnCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return 0;

	// FIXME: Implement me!
}

bool WalletsModel::hasChildren(const QModelIndex &parent) const
{
	// FIXME: Implement me!
}

bool WalletsModel::canFetchMore(const QModelIndex &parent) const
{
	// FIXME: Implement me!
	return false;
}

void WalletsModel::fetchMore(const QModelIndex &parent)
{
	// FIXME: Implement me!
}

QVariant WalletsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// FIXME: Implement me!
	return QVariant();
}

bool WalletsModel::insertRows(int row, int count, const QModelIndex &parent)
{
	beginInsertRows(parent, row, row + count - 1);
	// FIXME: Implement me!
	endInsertRows();
}

bool WalletsModel::insertColumns(int column, int count, const QModelIndex &parent)
{
	beginInsertColumns(parent, column, column + count - 1);
	// FIXME: Implement me!
	endInsertColumns();
}

bool WalletsModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	// FIXME: Implement me!
	endRemoveRows();
}

bool WalletsModel::removeColumns(int column, int count, const QModelIndex &parent)
{
	beginRemoveColumns(parent, column, column + count - 1);
	// FIXME: Implement me!
	endRemoveColumns();
}
