#!/usr/bin/env python
import sys
import vtk
from vtk.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

# Prevent .pyc files being created.
# Stops the vtk source being polluted
# by .pyc files.
sys.dont_write_bytecode = True

import backdrop

# Contour every quadratic cell type
# Create a scene with one of each cell type.

# QuadraticEdge
edgePoints = vtk.vtkPoints()
edgePoints.SetNumberOfPoints(3)
edgePoints.InsertPoint(0, 0, 0, 0)
edgePoints.InsertPoint(1, 1.0, 0, 0)
edgePoints.InsertPoint(2, 0.5, 0.25, 0)
edgeScalars = vtk.vtkFloatArray()
edgeScalars.SetNumberOfTuples(3)
edgeScalars.InsertValue(0, 0.0)
edgeScalars.InsertValue(1, 0.0)
edgeScalars.InsertValue(2, 0.9)
aEdge = vtk.vtkQuadraticEdge()
aEdge.GetPointIds().SetId(0, 0)
aEdge.GetPointIds().SetId(1, 1)
aEdge.GetPointIds().SetId(2, 2)
aEdgeGrid = vtk.vtkUnstructuredGrid()
aEdgeGrid.Allocate(1, 1)
aEdgeGrid.InsertNextCell(aEdge.GetCellType(), aEdge.GetPointIds())
aEdgeGrid.SetPoints(edgePoints)
aEdgeGrid.GetPointData().SetScalars(edgeScalars)
edgeContours = vtk.vtkContourFilter()
edgeContours.SetInputData(aEdgeGrid)
edgeContours.SetValue(0, 0.5)
aEdgeContourMapper = vtk.vtkDataSetMapper()
aEdgeContourMapper.SetInputConnection(edgeContours.GetOutputPort())
aEdgeContourMapper.ScalarVisibilityOff()
aEdgeMapper = vtk.vtkDataSetMapper()
aEdgeMapper.SetInputData(aEdgeGrid)
aEdgeMapper.ScalarVisibilityOff()
aEdgeActor = vtk.vtkActor()
aEdgeActor.SetMapper(aEdgeMapper)
aEdgeActor.GetProperty().SetRepresentationToWireframe()
aEdgeActor.GetProperty().SetAmbient(1.0)
aEdgeContourActor = vtk.vtkActor()
aEdgeContourActor.SetMapper(aEdgeContourMapper)
aEdgeContourActor.GetProperty().BackfaceCullingOn()
aEdgeContourActor.GetProperty().SetAmbient(1.0)

# Quadratic triangle
triPoints = vtk.vtkPoints()
triPoints.SetNumberOfPoints(6)
triPoints.InsertPoint(0, 0.0, 0.0, 0.0)
triPoints.InsertPoint(1, 1.0, 0.0, 0.0)
triPoints.InsertPoint(2, 0.5, 0.8, 0.0)
triPoints.InsertPoint(3, 0.5, 0.0, 0.0)
triPoints.InsertPoint(4, 0.75, 0.4, 0.0)
triPoints.InsertPoint(5, 0.25, 0.4, 0.0)
triScalars = vtk.vtkFloatArray()
triScalars.SetNumberOfTuples(6)
triScalars.InsertValue(0, 0.0)
triScalars.InsertValue(1, 0.0)
triScalars.InsertValue(2, 0.0)
triScalars.InsertValue(3, 1.0)
triScalars.InsertValue(4, 0.0)
triScalars.InsertValue(5, 0.0)
aTri = vtk.vtkQuadraticTriangle()
aTri.GetPointIds().SetId(0, 0)
aTri.GetPointIds().SetId(1, 1)
aTri.GetPointIds().SetId(2, 2)
aTri.GetPointIds().SetId(3, 3)
aTri.GetPointIds().SetId(4, 4)
aTri.GetPointIds().SetId(5, 5)
aTriGrid = vtk.vtkUnstructuredGrid()
aTriGrid.Allocate(1, 1)
aTriGrid.InsertNextCell(aTri.GetCellType(), aTri.GetPointIds())
aTriGrid.SetPoints(triPoints)
aTriGrid.GetPointData().SetScalars(triScalars)
triContours = vtk.vtkContourFilter()
triContours.SetInputData(aTriGrid)
triContours.SetValue(0, 0.5)
aTriContourMapper = vtk.vtkDataSetMapper()
aTriContourMapper.SetInputConnection(triContours.GetOutputPort())
aTriContourMapper.ScalarVisibilityOff()
aTriMapper = vtk.vtkDataSetMapper()
aTriMapper.SetInputData(aTriGrid)
aTriMapper.ScalarVisibilityOff()
aTriActor = vtk.vtkActor()
aTriActor.SetMapper(aTriMapper)
aTriActor.GetProperty().SetRepresentationToWireframe()
aTriActor.GetProperty().SetAmbient(1.0)
aTriContourActor = vtk.vtkActor()
aTriContourActor.SetMapper(aTriContourMapper)
aTriContourActor.GetProperty().BackfaceCullingOn()
aTriContourActor.GetProperty().SetAmbient(1.0)

# Quadratic quadrilateral
quadPoints = vtk.vtkPoints()
quadPoints.SetNumberOfPoints(8)
quadPoints.InsertPoint(0, 0.0, 0.0, 0.0)
quadPoints.InsertPoint(1, 1.0, 0.0, 0.0)
quadPoints.InsertPoint(2, 1.0, 1.0, 0.0)
quadPoints.InsertPoint(3, 0.0, 1.0, 0.0)
quadPoints.InsertPoint(4, 0.5, 0.0, 0.0)
quadPoints.InsertPoint(5, 1.0, 0.5, 0.0)
quadPoints.InsertPoint(6, 0.5, 1.0, 0.0)
quadPoints.InsertPoint(7, 0.0, 0.5, 0.0)
quadScalars = vtk.vtkFloatArray()
quadScalars.SetNumberOfTuples(8)
quadScalars.InsertValue(0, 0.0)
quadScalars.InsertValue(1, 0.0)
quadScalars.InsertValue(2, 1.0)
quadScalars.InsertValue(3, 1.0)
quadScalars.InsertValue(4, 1.0)
quadScalars.InsertValue(5, 0.0)
quadScalars.InsertValue(6, 0.0)
quadScalars.InsertValue(7, 0.0)
aQuad = vtk.vtkQuadraticQuad()
aQuad.GetPointIds().SetId(0, 0)
aQuad.GetPointIds().SetId(1, 1)
aQuad.GetPointIds().SetId(2, 2)
aQuad.GetPointIds().SetId(3, 3)
aQuad.GetPointIds().SetId(4, 4)
aQuad.GetPointIds().SetId(5, 5)
aQuad.GetPointIds().SetId(6, 6)
aQuad.GetPointIds().SetId(7, 7)
aQuadGrid = vtk.vtkUnstructuredGrid()
aQuadGrid.Allocate(1, 1)
aQuadGrid.InsertNextCell(aQuad.GetCellType(), aQuad.GetPointIds())
aQuadGrid.SetPoints(quadPoints)
aQuadGrid.GetPointData().SetScalars(quadScalars)
quadContours = vtk.vtkContourFilter()
quadContours.SetInputData(aQuadGrid)
quadContours.SetValue(0, 0.5)
aQuadContourMapper = vtk.vtkDataSetMapper()
aQuadContourMapper.SetInputConnection(quadContours.GetOutputPort())
aQuadContourMapper.ScalarVisibilityOff()
aQuadMapper = vtk.vtkDataSetMapper()
aQuadMapper.SetInputData(aQuadGrid)
aQuadMapper.ScalarVisibilityOff()
aQuadActor = vtk.vtkActor()
aQuadActor.SetMapper(aQuadMapper)
aQuadActor.GetProperty().SetRepresentationToWireframe()
aQuadActor.GetProperty().SetAmbient(1.0)
aQuadContourActor = vtk.vtkActor()
aQuadContourActor.SetMapper(aQuadContourMapper)
aQuadContourActor.GetProperty().BackfaceCullingOn()
aQuadContourActor.GetProperty().SetAmbient(1.0)

# BiQuadratic quadrilateral
BquadPoints = vtk.vtkPoints()
BquadPoints.SetNumberOfPoints(9)
BquadPoints.InsertPoint(0, 0.0, 0.0, 0.0)
BquadPoints.InsertPoint(1, 1.0, 0.0, 0.0)
BquadPoints.InsertPoint(2, 1.0, 1.0, 0.0)
BquadPoints.InsertPoint(3, 0.0, 1.0, 0.0)
BquadPoints.InsertPoint(4, 0.5, 0.0, 0.0)
BquadPoints.InsertPoint(5, 1.0, 0.5, 0.0)
BquadPoints.InsertPoint(6, 0.5, 1.0, 0.0)
BquadPoints.InsertPoint(7, 0.0, 0.5, 0.0)
BquadPoints.InsertPoint(8, 0.5, 0.5, 0.0)
BquadScalars = vtk.vtkFloatArray()
BquadScalars.SetNumberOfTuples(9)
BquadScalars.InsertValue(0, 1.0)
BquadScalars.InsertValue(1, 1.0)
BquadScalars.InsertValue(2, 1.0)
BquadScalars.InsertValue(3, 1.0)
BquadScalars.InsertValue(4, 0.0)
BquadScalars.InsertValue(5, 0.0)
BquadScalars.InsertValue(6, 0.0)
BquadScalars.InsertValue(7, 0.0)
BquadScalars.InsertValue(8, 1.0)
BQuad = vtk.vtkBiQuadraticQuad()
BQuad.GetPointIds().SetId(0, 0)
BQuad.GetPointIds().SetId(1, 1)
BQuad.GetPointIds().SetId(2, 2)
BQuad.GetPointIds().SetId(3, 3)
BQuad.GetPointIds().SetId(4, 4)
BQuad.GetPointIds().SetId(5, 5)
BQuad.GetPointIds().SetId(6, 6)
BQuad.GetPointIds().SetId(7, 7)
BQuad.GetPointIds().SetId(8, 8)
BQuadGrid = vtk.vtkUnstructuredGrid()
BQuadGrid.Allocate(1, 1)
BQuadGrid.InsertNextCell(BQuad.GetCellType(), BQuad.GetPointIds())
BQuadGrid.SetPoints(BquadPoints)
BQuadGrid.GetPointData().SetScalars(BquadScalars)
BquadContours = vtk.vtkContourFilter()
BquadContours.SetInputData(BQuadGrid)
BquadContours.SetValue(0, 0.5)
BQuadContourMapper = vtk.vtkDataSetMapper()
BQuadContourMapper.SetInputConnection(BquadContours.GetOutputPort())
BQuadContourMapper.ScalarVisibilityOff()
BQuadMapper = vtk.vtkDataSetMapper()
BQuadMapper.SetInputData(BQuadGrid)
BQuadMapper.ScalarVisibilityOff()
BQuadActor = vtk.vtkActor()
BQuadActor.SetMapper(BQuadMapper)
BQuadActor.GetProperty().SetRepresentationToWireframe()
BQuadActor.GetProperty().SetAmbient(1.0)
BQuadContourActor = vtk.vtkActor()
BQuadContourActor.SetMapper(BQuadContourMapper)
BQuadContourActor.GetProperty().BackfaceCullingOn()
BQuadContourActor.GetProperty().SetAmbient(1.0)

# Quadratic linear quadrilateral
QLquadPoints = vtk.vtkPoints()
QLquadPoints.SetNumberOfPoints(6)
QLquadPoints.InsertPoint(0, 0.0, 0.0, 0.0)
QLquadPoints.InsertPoint(1, 1.0, 0.0, 0.0)
QLquadPoints.InsertPoint(2, 1.0, 1.0, 0.0)
QLquadPoints.InsertPoint(3, 0.0, 1.0, 0.0)
QLquadPoints.InsertPoint(4, 0.5, 0.0, 0.0)
QLquadPoints.InsertPoint(5, 0.5, 1.0, 0.0)
QLquadScalars = vtk.vtkFloatArray()
QLquadScalars.SetNumberOfTuples(6)
QLquadScalars.InsertValue(0, 1.0)
QLquadScalars.InsertValue(1, 1.0)
QLquadScalars.InsertValue(2, 0.0)
QLquadScalars.InsertValue(3, 0.0)
QLquadScalars.InsertValue(4, 0.0)
QLquadScalars.InsertValue(5, 1.0)
QLQuad = vtk.vtkQuadraticLinearQuad()
QLQuad.GetPointIds().SetId(0, 0)
QLQuad.GetPointIds().SetId(1, 1)
QLQuad.GetPointIds().SetId(2, 2)
QLQuad.GetPointIds().SetId(3, 3)
QLQuad.GetPointIds().SetId(4, 4)
QLQuad.GetPointIds().SetId(5, 5)
QLQuadGrid = vtk.vtkUnstructuredGrid()
QLQuadGrid.Allocate(1, 1)
QLQuadGrid.InsertNextCell(QLQuad.GetCellType(), QLQuad.GetPointIds())
QLQuadGrid.SetPoints(QLquadPoints)
QLQuadGrid.GetPointData().SetScalars(QLquadScalars)
QLquadContours = vtk.vtkContourFilter()
QLquadContours.SetInputData(QLQuadGrid)
QLquadContours.SetValue(0, 0.5)
QLQuadContourMapper = vtk.vtkDataSetMapper()
QLQuadContourMapper.SetInputConnection(QLquadContours.GetOutputPort())
QLQuadContourMapper.ScalarVisibilityOff()
QLQuadMapper = vtk.vtkDataSetMapper()
QLQuadMapper.SetInputData(QLQuadGrid)
QLQuadMapper.ScalarVisibilityOff()
QLQuadActor = vtk.vtkActor()
QLQuadActor.SetMapper(QLQuadMapper)
QLQuadActor.GetProperty().SetRepresentationToWireframe()
QLQuadActor.GetProperty().SetAmbient(1.0)
QLQuadContourActor = vtk.vtkActor()
QLQuadContourActor.SetMapper(QLQuadContourMapper)
QLQuadContourActor.GetProperty().BackfaceCullingOn()
QLQuadContourActor.GetProperty().SetAmbient(1.0)

# Quadratic tetrahedron
tetPoints = vtk.vtkPoints()
tetPoints.SetNumberOfPoints(10)
tetPoints.InsertPoint(0, 0.0, 0.0, 0.0)
tetPoints.InsertPoint(1, 1.0, 0.0, 0.0)
tetPoints.InsertPoint(2, 0.5, 0.8, 0.0)
tetPoints.InsertPoint(3, 0.5, 0.4, 1.0)
tetPoints.InsertPoint(4, 0.5, 0.0, 0.0)
tetPoints.InsertPoint(5, 0.75, 0.4, 0.0)
tetPoints.InsertPoint(6, 0.25, 0.4, 0.0)
tetPoints.InsertPoint(7, 0.25, 0.2, 0.5)
tetPoints.InsertPoint(8, 0.75, 0.2, 0.5)
tetPoints.InsertPoint(9, 0.50, 0.6, 0.5)
tetScalars = vtk.vtkFloatArray()
tetScalars.SetNumberOfTuples(10)
tetScalars.InsertValue(0, 1.0)
tetScalars.InsertValue(1, 1.0)
tetScalars.InsertValue(2, 1.0)
tetScalars.InsertValue(3, 1.0)
tetScalars.InsertValue(4, 0.0)
tetScalars.InsertValue(5, 0.0)
tetScalars.InsertValue(6, 0.0)
tetScalars.InsertValue(7, 0.0)
tetScalars.InsertValue(8, 0.0)
tetScalars.InsertValue(9, 0.0)
aTet = vtk.vtkQuadraticTetra()
aTet.GetPointIds().SetId(0, 0)
aTet.GetPointIds().SetId(1, 1)
aTet.GetPointIds().SetId(2, 2)
aTet.GetPointIds().SetId(3, 3)
aTet.GetPointIds().SetId(4, 4)
aTet.GetPointIds().SetId(5, 5)
aTet.GetPointIds().SetId(6, 6)
aTet.GetPointIds().SetId(7, 7)
aTet.GetPointIds().SetId(8, 8)
aTet.GetPointIds().SetId(9, 9)
aTetGrid = vtk.vtkUnstructuredGrid()
aTetGrid.Allocate(1, 1)
aTetGrid.InsertNextCell(aTet.GetCellType(), aTet.GetPointIds())
aTetGrid.SetPoints(tetPoints)
aTetGrid.GetPointData().SetScalars(tetScalars)
tetContours = vtk.vtkContourFilter()
tetContours.SetInputData(aTetGrid)
tetContours.SetValue(0, 0.5)
aTetContourMapper = vtk.vtkDataSetMapper()
aTetContourMapper.SetInputConnection(tetContours.GetOutputPort())
aTetContourMapper.ScalarVisibilityOff()
aTetMapper = vtk.vtkDataSetMapper()
aTetMapper.SetInputData(aTetGrid)
aTetMapper.ScalarVisibilityOff()
aTetActor = vtk.vtkActor()
aTetActor.SetMapper(aTetMapper)
aTetActor.GetProperty().SetRepresentationToWireframe()
aTetActor.GetProperty().SetAmbient(1.0)
aTetContourActor = vtk.vtkActor()
aTetContourActor.SetMapper(aTetContourMapper)
aTetContourActor.GetProperty().SetAmbient(1.0)

# Quadratic hexahedron
hexPoints = vtk.vtkPoints()
hexPoints.SetNumberOfPoints(20)
hexPoints.InsertPoint(0, 0, 0, 0)
hexPoints.InsertPoint(1, 1, 0, 0)
hexPoints.InsertPoint(2, 1, 1, 0)
hexPoints.InsertPoint(3, 0, 1, 0)
hexPoints.InsertPoint(4, 0, 0, 1)
hexPoints.InsertPoint(5, 1, 0, 1)
hexPoints.InsertPoint(6, 1, 1, 1)
hexPoints.InsertPoint(7, 0, 1, 1)
hexPoints.InsertPoint(8, 0.5, 0, 0)
hexPoints.InsertPoint(9, 1, 0.5, 0)
hexPoints.InsertPoint(10, 0.5, 1, 0)
hexPoints.InsertPoint(11, 0, 0.5, 0)
hexPoints.InsertPoint(12, 0.5, 0, 1)
hexPoints.InsertPoint(13, 1, 0.5, 1)
hexPoints.InsertPoint(14, 0.5, 1, 1)
hexPoints.InsertPoint(15, 0, 0.5, 1)
hexPoints.InsertPoint(16, 0, 0, 0.5)
hexPoints.InsertPoint(17, 1, 0, 0.5)
hexPoints.InsertPoint(18, 1, 1, 0.5)
hexPoints.InsertPoint(19, 0, 1, 0.5)
hexScalars = vtk.vtkFloatArray()
hexScalars.SetNumberOfTuples(20)
hexScalars.InsertValue(0, 1.0)
hexScalars.InsertValue(1, 1.0)
hexScalars.InsertValue(2, 1.0)
hexScalars.InsertValue(3, 1.0)
hexScalars.InsertValue(4, 1.0)
hexScalars.InsertValue(5, 1.0)
hexScalars.InsertValue(6, 1.0)
hexScalars.InsertValue(7, 1.0)
hexScalars.InsertValue(8, 0.0)
hexScalars.InsertValue(9, 0.0)
hexScalars.InsertValue(10, 0.0)
hexScalars.InsertValue(11, 0.0)
hexScalars.InsertValue(12, 0.0)
hexScalars.InsertValue(13, 0.0)
hexScalars.InsertValue(14, 0.0)
hexScalars.InsertValue(15, 0.0)
hexScalars.InsertValue(16, 0.0)
hexScalars.InsertValue(17, 0.0)
hexScalars.InsertValue(18, 0.0)
hexScalars.InsertValue(19, 0.0)
aHex = vtk.vtkQuadraticHexahedron()
aHex.GetPointIds().SetId(0, 0)
aHex.GetPointIds().SetId(1, 1)
aHex.GetPointIds().SetId(2, 2)
aHex.GetPointIds().SetId(3, 3)
aHex.GetPointIds().SetId(4, 4)
aHex.GetPointIds().SetId(5, 5)
aHex.GetPointIds().SetId(6, 6)
aHex.GetPointIds().SetId(7, 7)
aHex.GetPointIds().SetId(8, 8)
aHex.GetPointIds().SetId(9, 9)
aHex.GetPointIds().SetId(10, 10)
aHex.GetPointIds().SetId(11, 11)
aHex.GetPointIds().SetId(12, 12)
aHex.GetPointIds().SetId(13, 13)
aHex.GetPointIds().SetId(14, 14)
aHex.GetPointIds().SetId(15, 15)
aHex.GetPointIds().SetId(16, 16)
aHex.GetPointIds().SetId(17, 17)
aHex.GetPointIds().SetId(18, 18)
aHex.GetPointIds().SetId(19, 19)
aHexGrid = vtk.vtkUnstructuredGrid()
aHexGrid.Allocate(1, 1)
aHexGrid.InsertNextCell(aHex.GetCellType(), aHex.GetPointIds())
aHexGrid.SetPoints(hexPoints)
aHexGrid.GetPointData().SetScalars(hexScalars)
hexContours = vtk.vtkContourFilter()
hexContours.SetInputData(aHexGrid)
hexContours.SetValue(0, 0.5)
aHexContourMapper = vtk.vtkDataSetMapper()
aHexContourMapper.SetInputConnection(hexContours.GetOutputPort())
aHexContourMapper.ScalarVisibilityOff()
aHexMapper = vtk.vtkDataSetMapper()
aHexMapper.SetInputData(aHexGrid)
aHexMapper.ScalarVisibilityOff()
aHexActor = vtk.vtkActor()
aHexActor.SetMapper(aHexMapper)
aHexActor.GetProperty().SetRepresentationToWireframe()
aHexActor.GetProperty().SetAmbient(1.0)
aHexContourActor = vtk.vtkActor()
aHexContourActor.SetMapper(aHexContourMapper)
aHexContourActor.GetProperty().SetAmbient(1.0)

# TriQuadratic hexahedron
TQhexPoints = vtk.vtkPoints()
TQhexPoints.SetNumberOfPoints(27)
TQhexPoints.InsertPoint(0, 0, 0, 0)
TQhexPoints.InsertPoint(1, 1, 0, 0)
TQhexPoints.InsertPoint(2, 1, 1, 0)
TQhexPoints.InsertPoint(3, 0, 1, 0)
TQhexPoints.InsertPoint(4, 0, 0, 1)
TQhexPoints.InsertPoint(5, 1, 0, 1)
TQhexPoints.InsertPoint(6, 1, 1, 1)
TQhexPoints.InsertPoint(7, 0, 1, 1)
TQhexPoints.InsertPoint(8, 0.5, 0, 0)
TQhexPoints.InsertPoint(9, 1, 0.5, 0)
TQhexPoints.InsertPoint(10, 0.5, 1, 0)
TQhexPoints.InsertPoint(11, 0, 0.5, 0)
TQhexPoints.InsertPoint(12, 0.5, 0, 1)
TQhexPoints.InsertPoint(13, 1, 0.5, 1)
TQhexPoints.InsertPoint(14, 0.5, 1, 1)
TQhexPoints.InsertPoint(15, 0, 0.5, 1)
TQhexPoints.InsertPoint(16, 0, 0, 0.5)
TQhexPoints.InsertPoint(17, 1, 0, 0.5)
TQhexPoints.InsertPoint(18, 1, 1, 0.5)
TQhexPoints.InsertPoint(19, 0, 1, 0.5)
TQhexPoints.InsertPoint(22, 0.5, 0, 0.5)
TQhexPoints.InsertPoint(21, 1, 0.5, 0.5)
TQhexPoints.InsertPoint(23, 0.5, 1, 0.5)
TQhexPoints.InsertPoint(20, 0, 0.5, 0.5)
TQhexPoints.InsertPoint(24, 0.5, 0.5, 0.0)
TQhexPoints.InsertPoint(25, 0.5, 0.5, 1)
TQhexPoints.InsertPoint(26, 0.5, 0.5, 0.5)
TQhexScalars = vtk.vtkFloatArray()
TQhexScalars.SetNumberOfTuples(27)
TQhexScalars.InsertValue(0, 1.0)
TQhexScalars.InsertValue(1, 1.0)
TQhexScalars.InsertValue(2, 1.0)
TQhexScalars.InsertValue(3, 1.0)
TQhexScalars.InsertValue(4, 1.0)
TQhexScalars.InsertValue(5, 1.0)
TQhexScalars.InsertValue(6, 1.0)
TQhexScalars.InsertValue(7, 1.0)
TQhexScalars.InsertValue(8, 0.0)
TQhexScalars.InsertValue(9, 0.0)
TQhexScalars.InsertValue(10, 0.0)
TQhexScalars.InsertValue(11, 0.0)
TQhexScalars.InsertValue(12, 0.0)
TQhexScalars.InsertValue(13, 0.0)
TQhexScalars.InsertValue(14, 0.0)
TQhexScalars.InsertValue(15, 0.0)
TQhexScalars.InsertValue(16, 0.0)
TQhexScalars.InsertValue(17, 0.0)
TQhexScalars.InsertValue(18, 0.0)
TQhexScalars.InsertValue(19, 0.0)
TQhexScalars.InsertValue(20, 0.0)
TQhexScalars.InsertValue(21, 0.0)
TQhexScalars.InsertValue(22, 0.0)
TQhexScalars.InsertValue(23, 0.0)
TQhexScalars.InsertValue(24, 0.0)
TQhexScalars.InsertValue(25, 0.0)
TQhexScalars.InsertValue(26, 1.0)
TQHex = vtk.vtkTriQuadraticHexahedron()
TQHex.GetPointIds().SetId(0, 0)
TQHex.GetPointIds().SetId(1, 1)
TQHex.GetPointIds().SetId(2, 2)
TQHex.GetPointIds().SetId(3, 3)
TQHex.GetPointIds().SetId(4, 4)
TQHex.GetPointIds().SetId(5, 5)
TQHex.GetPointIds().SetId(6, 6)
TQHex.GetPointIds().SetId(7, 7)
TQHex.GetPointIds().SetId(8, 8)
TQHex.GetPointIds().SetId(9, 9)
TQHex.GetPointIds().SetId(10, 10)
TQHex.GetPointIds().SetId(11, 11)
TQHex.GetPointIds().SetId(12, 12)
TQHex.GetPointIds().SetId(13, 13)
TQHex.GetPointIds().SetId(14, 14)
TQHex.GetPointIds().SetId(15, 15)
TQHex.GetPointIds().SetId(16, 16)
TQHex.GetPointIds().SetId(17, 17)
TQHex.GetPointIds().SetId(18, 18)
TQHex.GetPointIds().SetId(19, 19)
TQHex.GetPointIds().SetId(20, 20)
TQHex.GetPointIds().SetId(21, 21)
TQHex.GetPointIds().SetId(22, 22)
TQHex.GetPointIds().SetId(23, 23)
TQHex.GetPointIds().SetId(24, 24)
TQHex.GetPointIds().SetId(25, 25)
TQHex.GetPointIds().SetId(26, 26)
TQHexGrid = vtk.vtkUnstructuredGrid()
TQHexGrid.Allocate(1, 1)
TQHexGrid.InsertNextCell(TQHex.GetCellType(), TQHex.GetPointIds())
TQHexGrid.SetPoints(TQhexPoints)
TQHexGrid.GetPointData().SetScalars(TQhexScalars)
TQhexContours = vtk.vtkContourFilter()
TQhexContours.SetInputData(TQHexGrid)
TQhexContours.SetValue(0, 0.5)
TQHexContourMapper = vtk.vtkDataSetMapper()
TQHexContourMapper.SetInputConnection(TQhexContours.GetOutputPort())
TQHexContourMapper.ScalarVisibilityOff()
TQHexMapper = vtk.vtkDataSetMapper()
TQHexMapper.SetInputData(TQHexGrid)
TQHexMapper.ScalarVisibilityOff()
TQHexActor = vtk.vtkActor()
TQHexActor.SetMapper(TQHexMapper)
TQHexActor.GetProperty().SetRepresentationToWireframe()
TQHexActor.GetProperty().SetAmbient(1.0)
TQHexContourActor = vtk.vtkActor()
TQHexContourActor.SetMapper(TQHexContourMapper)
TQHexContourActor.GetProperty().SetAmbient(1.0)

# BiQuadratic Quadratic hexahedron
BQhexPoints = vtk.vtkPoints()
BQhexPoints.SetNumberOfPoints(24)
BQhexPoints.InsertPoint(0, 0, 0, 0)
BQhexPoints.InsertPoint(1, 1, 0, 0)
BQhexPoints.InsertPoint(2, 1, 1, 0)
BQhexPoints.InsertPoint(3, 0, 1, 0)
BQhexPoints.InsertPoint(4, 0, 0, 1)
BQhexPoints.InsertPoint(5, 1, 0, 1)
BQhexPoints.InsertPoint(6, 1, 1, 1)
BQhexPoints.InsertPoint(7, 0, 1, 1)
BQhexPoints.InsertPoint(8, 0.5, 0, 0)
BQhexPoints.InsertPoint(9, 1, 0.5, 0)
BQhexPoints.InsertPoint(10, 0.5, 1, 0)
BQhexPoints.InsertPoint(11, 0, 0.5, 0)
BQhexPoints.InsertPoint(12, 0.5, 0, 1)
BQhexPoints.InsertPoint(13, 1, 0.5, 1)
BQhexPoints.InsertPoint(14, 0.5, 1, 1)
BQhexPoints.InsertPoint(15, 0, 0.5, 1)
BQhexPoints.InsertPoint(16, 0, 0, 0.5)
BQhexPoints.InsertPoint(17, 1, 0, 0.5)
BQhexPoints.InsertPoint(18, 1, 1, 0.5)
BQhexPoints.InsertPoint(19, 0, 1, 0.5)
BQhexPoints.InsertPoint(22, 0.5, 0, 0.5)
BQhexPoints.InsertPoint(21, 1, 0.5, 0.5)
BQhexPoints.InsertPoint(23, 0.5, 1, 0.5)
BQhexPoints.InsertPoint(20, 0, 0.5, 0.5)
BQhexScalars = vtk.vtkFloatArray()
BQhexScalars.SetNumberOfTuples(24)
BQhexScalars.InsertValue(0, 1.0)
BQhexScalars.InsertValue(1, 1.0)
BQhexScalars.InsertValue(2, 1.0)
BQhexScalars.InsertValue(3, 1.0)
BQhexScalars.InsertValue(4, 1.0)
BQhexScalars.InsertValue(5, 1.0)
BQhexScalars.InsertValue(6, 1.0)
BQhexScalars.InsertValue(7, 1.0)
BQhexScalars.InsertValue(8, 0.0)
BQhexScalars.InsertValue(9, 0.0)
BQhexScalars.InsertValue(10, 0.0)
BQhexScalars.InsertValue(11, 0.0)
BQhexScalars.InsertValue(12, 0.0)
BQhexScalars.InsertValue(13, 0.0)
BQhexScalars.InsertValue(14, 0.0)
BQhexScalars.InsertValue(15, 0.0)
BQhexScalars.InsertValue(16, 0.0)
BQhexScalars.InsertValue(17, 0.0)
BQhexScalars.InsertValue(18, 0.0)
BQhexScalars.InsertValue(19, 0.0)
BQhexScalars.InsertValue(20, 0.0)
BQhexScalars.InsertValue(21, 0.0)
BQhexScalars.InsertValue(22, 0.0)
BQhexScalars.InsertValue(23, 0.0)
BQHex = vtk.vtkBiQuadraticQuadraticHexahedron()
BQHex.GetPointIds().SetId(0, 0)
BQHex.GetPointIds().SetId(1, 1)
BQHex.GetPointIds().SetId(2, 2)
BQHex.GetPointIds().SetId(3, 3)
BQHex.GetPointIds().SetId(4, 4)
BQHex.GetPointIds().SetId(5, 5)
BQHex.GetPointIds().SetId(6, 6)
BQHex.GetPointIds().SetId(7, 7)
BQHex.GetPointIds().SetId(8, 8)
BQHex.GetPointIds().SetId(9, 9)
BQHex.GetPointIds().SetId(10, 10)
BQHex.GetPointIds().SetId(11, 11)
BQHex.GetPointIds().SetId(12, 12)
BQHex.GetPointIds().SetId(13, 13)
BQHex.GetPointIds().SetId(14, 14)
BQHex.GetPointIds().SetId(15, 15)
BQHex.GetPointIds().SetId(16, 16)
BQHex.GetPointIds().SetId(17, 17)
BQHex.GetPointIds().SetId(18, 18)
BQHex.GetPointIds().SetId(19, 19)
BQHex.GetPointIds().SetId(20, 20)
BQHex.GetPointIds().SetId(21, 21)
BQHex.GetPointIds().SetId(22, 22)
BQHex.GetPointIds().SetId(23, 23)
BQHexGrid = vtk.vtkUnstructuredGrid()
BQHexGrid.Allocate(1, 1)
BQHexGrid.InsertNextCell(BQHex.GetCellType(), BQHex.GetPointIds())
BQHexGrid.SetPoints(BQhexPoints)
BQHexGrid.GetPointData().SetScalars(BQhexScalars)
BQhexContours = vtk.vtkContourFilter()
BQhexContours.SetInputData(BQHexGrid)
BQhexContours.SetValue(0, 0.5)
BQHexContourMapper = vtk.vtkDataSetMapper()
BQHexContourMapper.SetInputConnection(BQhexContours.GetOutputPort())
BQHexContourMapper.ScalarVisibilityOff()
BQHexMapper = vtk.vtkDataSetMapper()
BQHexMapper.SetInputData(BQHexGrid)
BQHexMapper.ScalarVisibilityOff()
BQHexActor = vtk.vtkActor()
BQHexActor.SetMapper(BQHexMapper)
BQHexActor.GetProperty().SetRepresentationToWireframe()
BQHexActor.GetProperty().SetAmbient(1.0)
BQHexContourActor = vtk.vtkActor()
BQHexContourActor.SetMapper(BQHexContourMapper)
BQHexContourActor.GetProperty().SetAmbient(1.0)

# Quadratic wedge
wedgePoints = vtk.vtkPoints()
wedgePoints.SetNumberOfPoints(15)
wedgePoints.InsertPoint(0, 0, 0, 0)
wedgePoints.InsertPoint(1, 1, 0, 0)
wedgePoints.InsertPoint(2, 0, 1, 0)
wedgePoints.InsertPoint(3, 0, 0, 1)
wedgePoints.InsertPoint(4, 1, 0, 1)
wedgePoints.InsertPoint(5, 0, 1, 1)
wedgePoints.InsertPoint(6, 0.5, 0, 0)
wedgePoints.InsertPoint(7, 0.5, 0.5, 0)
wedgePoints.InsertPoint(8, 0, 0.5, 0)
wedgePoints.InsertPoint(9, 0.5, 0, 1)
wedgePoints.InsertPoint(10, 0.5, 0.5, 1)
wedgePoints.InsertPoint(11, 0, 0.5, 1)
wedgePoints.InsertPoint(12, 0, 0, 0.5)
wedgePoints.InsertPoint(13, 1, 0, 0.5)
wedgePoints.InsertPoint(14, 0, 1, 0.5)
wedgeScalars = vtk.vtkFloatArray()
wedgeScalars.SetNumberOfTuples(15)
wedgeScalars.InsertValue(0, 1.0)
wedgeScalars.InsertValue(1, 1.0)
wedgeScalars.InsertValue(2, 1.0)
wedgeScalars.InsertValue(3, 1.0)
wedgeScalars.InsertValue(4, 1.0)
wedgeScalars.InsertValue(5, 1.0)
wedgeScalars.InsertValue(6, 0.0)
wedgeScalars.InsertValue(7, 0.0)
wedgeScalars.InsertValue(8, 0.0)
wedgeScalars.InsertValue(9, 0.0)
wedgeScalars.InsertValue(10, 0.0)
wedgeScalars.InsertValue(11, 0.0)
wedgeScalars.InsertValue(12, 0.0)
wedgeScalars.InsertValue(13, 0.0)
wedgeScalars.InsertValue(14, 0.0)
aWedge = vtk.vtkQuadraticWedge()
aWedge.GetPointIds().SetId(0, 0)
aWedge.GetPointIds().SetId(1, 1)
aWedge.GetPointIds().SetId(2, 2)
aWedge.GetPointIds().SetId(3, 3)
aWedge.GetPointIds().SetId(4, 4)
aWedge.GetPointIds().SetId(5, 5)
aWedge.GetPointIds().SetId(6, 6)
aWedge.GetPointIds().SetId(7, 7)
aWedge.GetPointIds().SetId(8, 8)
aWedge.GetPointIds().SetId(9, 9)
aWedge.GetPointIds().SetId(10, 10)
aWedge.GetPointIds().SetId(11, 11)
aWedge.GetPointIds().SetId(12, 12)
aWedge.GetPointIds().SetId(13, 13)
aWedge.GetPointIds().SetId(14, 14)
aWedgeGrid = vtk.vtkUnstructuredGrid()
aWedgeGrid.Allocate(1, 1)
aWedgeGrid.InsertNextCell(aWedge.GetCellType(), aWedge.GetPointIds())
aWedgeGrid.SetPoints(wedgePoints)
aWedgeGrid.GetPointData().SetScalars(wedgeScalars)
wedgeContours = vtk.vtkContourFilter()
wedgeContours.SetInputData(aWedgeGrid)
wedgeContours.SetValue(0, 0.5)
aWedgeContourMapper = vtk.vtkDataSetMapper()
aWedgeContourMapper.SetInputConnection(wedgeContours.GetOutputPort())
aWedgeContourMapper.ScalarVisibilityOff()
aWedgeMapper = vtk.vtkDataSetMapper()
aWedgeMapper.SetInputData(aWedgeGrid)
aWedgeMapper.ScalarVisibilityOff()
aWedgeActor = vtk.vtkActor()
aWedgeActor.SetMapper(aWedgeMapper)
aWedgeActor.GetProperty().SetRepresentationToWireframe()
aWedgeActor.GetProperty().SetAmbient(1.0)
aWedgeContourActor = vtk.vtkActor()
aWedgeContourActor.SetMapper(aWedgeContourMapper)
aWedgeContourActor.GetProperty().SetAmbient(1.0)

# Quadratic linear wedge
QLwedgePoints = vtk.vtkPoints()
QLwedgePoints.SetNumberOfPoints(12)
QLwedgePoints.InsertPoint(0, 0, 0, 0)
QLwedgePoints.InsertPoint(1, 1, 0, 0)
QLwedgePoints.InsertPoint(2, 0, 1, 0)
QLwedgePoints.InsertPoint(3, 0, 0, 1)
QLwedgePoints.InsertPoint(4, 1, 0, 1)
QLwedgePoints.InsertPoint(5, 0, 1, 1)
QLwedgePoints.InsertPoint(6, 0.5, 0, 0)
QLwedgePoints.InsertPoint(7, 0.5, 0.5, 0)
QLwedgePoints.InsertPoint(8, 0, 0.5, 0)
QLwedgePoints.InsertPoint(9, 0.5, 0, 1)
QLwedgePoints.InsertPoint(10, 0.5, 0.5, 1)
QLwedgePoints.InsertPoint(11, 0, 0.5, 1)
QLwedgeScalars = vtk.vtkFloatArray()
QLwedgeScalars.SetNumberOfTuples(12)
QLwedgeScalars.InsertValue(0, 1.0)
QLwedgeScalars.InsertValue(1, 1.0)
QLwedgeScalars.InsertValue(2, 1.0)
QLwedgeScalars.InsertValue(3, 1.0)
QLwedgeScalars.InsertValue(4, 1.0)
QLwedgeScalars.InsertValue(5, 1.0)
QLwedgeScalars.InsertValue(6, 0.0)
QLwedgeScalars.InsertValue(7, 0.0)
QLwedgeScalars.InsertValue(8, 0.0)
QLwedgeScalars.InsertValue(9, 0.0)
QLwedgeScalars.InsertValue(10, 0.0)
QLwedgeScalars.InsertValue(11, 0.0)
QLWedge = vtk.vtkQuadraticLinearWedge()
QLWedge.GetPointIds().SetId(0, 0)
QLWedge.GetPointIds().SetId(1, 1)
QLWedge.GetPointIds().SetId(2, 2)
QLWedge.GetPointIds().SetId(3, 3)
QLWedge.GetPointIds().SetId(4, 4)
QLWedge.GetPointIds().SetId(5, 5)
QLWedge.GetPointIds().SetId(6, 6)
QLWedge.GetPointIds().SetId(7, 7)
QLWedge.GetPointIds().SetId(8, 8)
QLWedge.GetPointIds().SetId(9, 9)
QLWedge.GetPointIds().SetId(10, 10)
QLWedge.GetPointIds().SetId(11, 11)
# QLWedge.DebugOn()
QLWedgeGrid = vtk.vtkUnstructuredGrid()
QLWedgeGrid.Allocate(1, 1)
QLWedgeGrid.InsertNextCell(QLWedge.GetCellType(), QLWedge.GetPointIds())
QLWedgeGrid.SetPoints(QLwedgePoints)
QLWedgeGrid.GetPointData().SetScalars(QLwedgeScalars)
QLwedgeContours = vtk.vtkContourFilter()
QLwedgeContours.SetInputData(QLWedgeGrid)
QLwedgeContours.SetValue(0, 0.5)
QLWedgeContourMapper = vtk.vtkDataSetMapper()
QLWedgeContourMapper.SetInputConnection(QLwedgeContours.GetOutputPort())
QLWedgeContourMapper.ScalarVisibilityOff()
QLWedgeMapper = vtk.vtkDataSetMapper()
QLWedgeMapper.SetInputData(QLWedgeGrid)
aWedgeMapper.ScalarVisibilityOff()
QLWedgeActor = vtk.vtkActor()
QLWedgeActor.SetMapper(QLWedgeMapper)
QLWedgeActor.GetProperty().SetRepresentationToWireframe()
QLWedgeActor.GetProperty().SetAmbient(1.0)
QLWedgeContourActor = vtk.vtkActor()
QLWedgeContourActor.SetMapper(QLWedgeContourMapper)
QLWedgeContourActor.GetProperty().SetAmbient(1.0)

# BiQuadratic wedge
BQwedgePoints = vtk.vtkPoints()
BQwedgePoints.SetNumberOfPoints(18)
BQwedgePoints.InsertPoint(0, 0, 0, 0)
BQwedgePoints.InsertPoint(1, 1, 0, 0)
BQwedgePoints.InsertPoint(2, 0, 1, 0)
BQwedgePoints.InsertPoint(3, 0, 0, 1)
BQwedgePoints.InsertPoint(4, 1, 0, 1)
BQwedgePoints.InsertPoint(5, 0, 1, 1)
BQwedgePoints.InsertPoint(6, 0.5, 0, 0)
BQwedgePoints.InsertPoint(7, 0.5, 0.5, 0)
BQwedgePoints.InsertPoint(8, 0, 0.5, 0)
BQwedgePoints.InsertPoint(9, 0.5, 0, 1)
BQwedgePoints.InsertPoint(10, 0.5, 0.5, 1)
BQwedgePoints.InsertPoint(11, 0, 0.5, 1)
BQwedgePoints.InsertPoint(12, 0, 0, 0.5)
BQwedgePoints.InsertPoint(13, 1, 0, 0.5)
BQwedgePoints.InsertPoint(14, 0, 1, 0.5)
BQwedgePoints.InsertPoint(15, 0.5, 0, 0.5)
BQwedgePoints.InsertPoint(16, 0.5, 0.5, 0.5)
BQwedgePoints.InsertPoint(17, 0, 0.5, 0.5)
BQwedgeScalars = vtk.vtkFloatArray()
BQwedgeScalars.SetNumberOfTuples(18)
BQwedgeScalars.InsertValue(0, 1.0)
BQwedgeScalars.InsertValue(1, 1.0)
BQwedgeScalars.InsertValue(2, 1.0)
BQwedgeScalars.InsertValue(3, 1.0)
BQwedgeScalars.InsertValue(4, 1.0)
BQwedgeScalars.InsertValue(5, 1.0)
BQwedgeScalars.InsertValue(6, 0.0)
BQwedgeScalars.InsertValue(7, 0.0)
BQwedgeScalars.InsertValue(8, 0.0)
BQwedgeScalars.InsertValue(9, 0.0)
BQwedgeScalars.InsertValue(10, 0.0)
BQwedgeScalars.InsertValue(11, 0.0)
BQwedgeScalars.InsertValue(12, 0.0)
BQwedgeScalars.InsertValue(13, 0.0)
BQwedgeScalars.InsertValue(14, 0.0)
BQwedgeScalars.InsertValue(15, 0.0)
BQwedgeScalars.InsertValue(16, 0.0)
BQwedgeScalars.InsertValue(17, 0.0)
BQWedge = vtk.vtkBiQuadraticQuadraticWedge()
BQWedge.GetPointIds().SetId(0, 0)
BQWedge.GetPointIds().SetId(1, 1)
BQWedge.GetPointIds().SetId(2, 2)
BQWedge.GetPointIds().SetId(3, 3)
BQWedge.GetPointIds().SetId(4, 4)
BQWedge.GetPointIds().SetId(5, 5)
BQWedge.GetPointIds().SetId(6, 6)
BQWedge.GetPointIds().SetId(7, 7)
BQWedge.GetPointIds().SetId(8, 8)
BQWedge.GetPointIds().SetId(9, 9)
BQWedge.GetPointIds().SetId(10, 10)
BQWedge.GetPointIds().SetId(11, 11)
BQWedge.GetPointIds().SetId(12, 12)
BQWedge.GetPointIds().SetId(13, 13)
BQWedge.GetPointIds().SetId(14, 14)
BQWedge.GetPointIds().SetId(15, 15)
BQWedge.GetPointIds().SetId(16, 16)
BQWedge.GetPointIds().SetId(17, 17)
# BQWedge.DebugOn()
BQWedgeGrid = vtk.vtkUnstructuredGrid()
BQWedgeGrid.Allocate(1, 1)
BQWedgeGrid.InsertNextCell(BQWedge.GetCellType(), BQWedge.GetPointIds())
BQWedgeGrid.SetPoints(BQwedgePoints)
BQWedgeGrid.GetPointData().SetScalars(BQwedgeScalars)
BQwedgeContours = vtk.vtkContourFilter()
BQwedgeContours.SetInputData(BQWedgeGrid)
BQwedgeContours.SetValue(0, 0.5)
BQWedgeContourMapper = vtk.vtkDataSetMapper()
BQWedgeContourMapper.SetInputConnection(BQwedgeContours.GetOutputPort())
# BQWedgeContourMapper.ScalarVisibilityOff()
BQWedgeMapper = vtk.vtkDataSetMapper()
BQWedgeMapper.SetInputData(BQWedgeGrid)
# BQWedgeMapper.ScalarVisibilityOff()
BQWedgeActor = vtk.vtkActor()
BQWedgeActor.SetMapper(BQWedgeMapper)
BQWedgeActor.GetProperty().SetRepresentationToWireframe()
BQWedgeActor.GetProperty().SetAmbient(1.0)
BQWedgeContourActor = vtk.vtkActor()
BQWedgeContourActor.SetMapper(BQWedgeContourMapper)
BQWedgeContourActor.GetProperty().SetAmbient(1.0)

# Quadratic pyramid
pyraPoints = vtk.vtkPoints()
pyraPoints.SetNumberOfPoints(13)
pyraPoints.InsertPoint(0, 0, 0, 0)
pyraPoints.InsertPoint(1, 1, 0, 0)
pyraPoints.InsertPoint(2, 1, 1, 0)
pyraPoints.InsertPoint(3, 0, 1, 0)
pyraPoints.InsertPoint(4, 0, 0, 1)
pyraPoints.InsertPoint(5, 0.5, 0, 0)
pyraPoints.InsertPoint(6, 1, 0.5, 0)
pyraPoints.InsertPoint(7, 0.5, 1, 0)
pyraPoints.InsertPoint(8, 0, 0.5, 0)
pyraPoints.InsertPoint(9, 0, 0, 0.5)
pyraPoints.InsertPoint(10, 0.5, 0, 0.5)
pyraPoints.InsertPoint(11, 0.5, 0.5, 0.5)
pyraPoints.InsertPoint(12, 0, 0.5, 0.5)
pyraScalars = vtk.vtkFloatArray()
pyraScalars.SetNumberOfTuples(13)
pyraScalars.InsertValue(0, 1.0)
pyraScalars.InsertValue(1, 1.0)
pyraScalars.InsertValue(2, 1.0)
pyraScalars.InsertValue(3, 1.0)
pyraScalars.InsertValue(4, 1.0)
pyraScalars.InsertValue(5, 0.0)
pyraScalars.InsertValue(6, 0.0)
pyraScalars.InsertValue(7, 0.0)
pyraScalars.InsertValue(8, 0.0)
pyraScalars.InsertValue(9, 0.0)
pyraScalars.InsertValue(10, 0.0)
pyraScalars.InsertValue(11, 0.0)
pyraScalars.InsertValue(12, 0.0)
aPyramid = vtk.vtkQuadraticPyramid()
aPyramid.GetPointIds().SetId(0, 0)
aPyramid.GetPointIds().SetId(1, 1)
aPyramid.GetPointIds().SetId(2, 2)
aPyramid.GetPointIds().SetId(3, 3)
aPyramid.GetPointIds().SetId(4, 4)
aPyramid.GetPointIds().SetId(5, 5)
aPyramid.GetPointIds().SetId(6, 6)
aPyramid.GetPointIds().SetId(7, 7)
aPyramid.GetPointIds().SetId(8, 8)
aPyramid.GetPointIds().SetId(9, 9)
aPyramid.GetPointIds().SetId(10, 10)
aPyramid.GetPointIds().SetId(11, 11)
aPyramid.GetPointIds().SetId(12, 12)
aPyramidGrid = vtk.vtkUnstructuredGrid()
aPyramidGrid.Allocate(1, 1)
aPyramidGrid.InsertNextCell(aPyramid.GetCellType(), aPyramid.GetPointIds())
aPyramidGrid.SetPoints(pyraPoints)
aPyramidGrid.GetPointData().SetScalars(pyraScalars)
pyraContours = vtk.vtkContourFilter()
pyraContours.SetInputData(aPyramidGrid)
pyraContours.SetValue(0, 0.5)
aPyramidContourMapper = vtk.vtkDataSetMapper()
aPyramidContourMapper.SetInputConnection(pyraContours.GetOutputPort())
aPyramidContourMapper.ScalarVisibilityOff()
aPyramidMapper = vtk.vtkDataSetMapper()
aPyramidMapper.SetInputData(aPyramidGrid)
aPyramidMapper.ScalarVisibilityOff()
aPyramidActor = vtk.vtkActor()
aPyramidActor.SetMapper(aPyramidMapper)
aPyramidActor.GetProperty().SetRepresentationToWireframe()
aPyramidActor.GetProperty().SetAmbient(1.0)
aPyramidContourActor = vtk.vtkActor()
aPyramidContourActor.SetMapper(aPyramidContourMapper)
aPyramidContourActor.GetProperty().SetAmbient(1.0)

# Create the rendering related stuff.
# Since some of our actors are a single vertex, we need to remove all
# cullers so the single vertex actors will render
ren1 = vtk.vtkRenderer()
ren1.GetCullers().RemoveAllItems()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren1)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren1.SetBackground(.1, .2, .3)

renWin.SetSize(400, 200)

# specify properties
ren1.AddActor(aEdgeActor)
ren1.AddActor(aEdgeContourActor)

ren1.AddActor(aTriActor)
ren1.AddActor(aTriContourActor)

ren1.AddActor(aQuadActor)
ren1.AddActor(aQuadContourActor)

ren1.AddActor(BQuadActor)
ren1.AddActor(BQuadContourActor)

ren1.AddActor(QLQuadActor)
ren1.AddActor(QLQuadContourActor)

ren1.AddActor(aTetActor)
ren1.AddActor(aTetContourActor)

ren1.AddActor(aHexActor)
ren1.AddActor(aHexContourActor)

ren1.AddActor(TQHexActor)
ren1.AddActor(TQHexContourActor)

ren1.AddActor(BQHexActor)
ren1.AddActor(BQHexContourActor)

ren1.AddActor(aWedgeActor)
ren1.AddActor(aWedgeContourActor)

ren1.AddActor(BQWedgeActor)
ren1.AddActor(BQWedgeContourActor)

ren1.AddActor(QLWedgeActor)
ren1.AddActor(QLWedgeContourActor)

ren1.AddActor(aPyramidActor)
ren1.AddActor(aPyramidContourActor)

# places everyone!!
aEdgeContourActor.AddPosition(0, 2, 0)
aTriActor.AddPosition(2, 0, 0)
aTriContourActor.AddPosition(2, 2, 0)
aQuadActor.AddPosition(4, 0, 0)
BQuadActor.AddPosition(4, 0, 2)
QLQuadActor.AddPosition(4, 0, 4)
aQuadContourActor.AddPosition(4, 2, 0)
BQuadContourActor.AddPosition(4, 2, 2)
QLQuadContourActor.AddPosition(4, 2, 4)
aTetActor.AddPosition(6, 0, 0)
aTetContourActor.AddPosition(6, 2, 0)
aHexActor.AddPosition(8, 0, 0)
TQHexActor.AddPosition(8, 0, 2)
BQHexActor.AddPosition(8, 0, 4)
aHexContourActor.AddPosition(8, 2, 0)
TQHexContourActor.AddPosition(8, 2, 2)
BQHexContourActor.AddPosition(8, 2, 4)
aWedgeActor.AddPosition(10, 0, 0)
QLWedgeActor.AddPosition(10, 0, 2)
BQWedgeActor.AddPosition(10, 0, 4)
aWedgeContourActor.AddPosition(10, 2, 0)
QLWedgeContourActor.AddPosition(10, 2, 2)
BQWedgeContourActor.AddPosition(10, 2, 4)
aPyramidActor.AddPosition(12, 0, 0)
aPyramidContourActor.AddPosition(12, 2, 0)

[base, back, left] = backdrop.BuildBackdrop(-1, 15, -1, 4, -1, 6, .1)

ren1.AddActor(base)
base.GetProperty().SetDiffuseColor(.2, .2, .2)
ren1.AddActor(left)
left.GetProperty().SetDiffuseColor(.2, .2, .2)
ren1.AddActor(back)
back.GetProperty().SetDiffuseColor(.2, .2, .2)

ren1.ResetCamera()
ren1.GetActiveCamera().Dolly(2.5)
ren1.ResetCameraClippingRange()

renWin.Render()

# render the image
#

iren.Initialize()
#iren.Start()
